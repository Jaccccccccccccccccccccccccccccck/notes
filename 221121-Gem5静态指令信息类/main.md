# Gem5静态指令信息类
> src/cpu/static_inst.hh

以静态指令信息基类**StaticInst**为研究对象

## 变量
- opcode（string）
- opClass 指令类别： 53类
  - No_OpClass,IntAlu,IntMult,IntDiv,FloatAdd,FloatCmp,FloatCvt,FloatMult,FloatMultAcc,FloatDiv,FloatMisc,FloatSqrt,SimdAdd,SimdAddAcc,SimdAlu,SimdCmp,SimdCvt,SimdMisc,SimdMult,SimdMultAcc,SimdShift,SimdShiftAcc,SimdDiv,SimdSqrt,SimdFloatAdd,SimdFloatAlu,SimdFloatCmp,SimdFloatCvt,SimdFloatDiv,SimdFloatMisc,SimdFloatMult,SimdFloatMultAcc,SimdFloatSqrt,SimdReduceAdd,SimdReduceAlu,SimdReduceCmp,SimdFloatReduceAdd,SimdFloatReduceCmp,SimdAes,SimdAesMix,SimdSha1Hash,SimdSha1Hash2,SimdSha256Hash,SimdSha256Hash2,SimdShaSigma2,SimdShaSigma3 ,SimdPredAlu,MemRead,MemWrite,FloatMemRead,FloatMemWrite,IprAccess,InstPrefetch

- 源、目标寄存器数量
  - _numSrcRegs
  - _numDestRegs
  - _numFPDestRegs
  - _numIntDestRegs
  - _numCCDestRegs
  - _numVecDestRegs
  - _numVecElemDestRegs
  - _numVecPredDestRegs
- 原目标寄存器指针
  - _srcRegIdxPtr
  - _destRegIdxPtr
- Flags：36个
  - IsNop,IsInteger,IsFloating,IsVector,IsVectorElem,IsLoad,IsStore,IsAtomic,IsStoreConditional,IsInstPrefetch,IsDataPrefetch,IsControl,IsDirectControl,IsIndirectControl,IsCondControl,IsUncondControl,IsCall,IsReturn,IsSerializing,IsSerializeBefore,IsSerializeAfter,IsWriteBarrier,IsReadBarrier,IsNonSpeculative,IsQuiesce,IsUnverifiable,IsSyscall,IsMacroop,IsMicroop,IsDelayedCommit,IsLastMicroop,IsFirstMicroop,IsSquashAfter,IsHtmStart,IsHtmStop,IsHtmCancel,Num_Flags
- 反汇编（string）
#### 指令信息类中为什么没有operands中？
具体的指令类使用继承关系在子类中根据指令类型增加operands变量，高层设计（StaticInst）中也无法确定是什么类型的operands

## 核心方法
- 指令执行（execute函数）
- 访存指令执行函数（initiateAcc、completeAcc）
- PC+1函数（advancePC）
- 构建返回地址(buildRetPC)
  - 当指令为return指令时，可以调用此方法返回一个地址
- 计算跳转地址函数
  - **非条件**跳转指令在**decode阶段**计算目标指令用于branchPredict判断（branchTarget:branch）

#### initateACC函数
调用链：
```
IEW::tick()
    IEW::executeInsts()
        LSQUnit->executeLoad() or LSQUnit::executeStore()
            inst->initiateAcc()
```
O3CPU中流水线阶段传输指令使用动态信息类，动态信息类如果是memRef类的指令，**IEW**阶段会调用动态指令类的initiateAcc方法，动态指令信息类方法实质上调用静态指令信息类，静态指令信息类initiateAcc方法第一个参数为动态指令信息类的指针
> src/cpu/o3/dyn_inst.cc
```
Fault
DynInst::initiateAcc()
{
    ...
    fault = staticInst->initiateAcc(this, traceData);
    ...
    return fault;
}
```
以LDRB64_IMM类实现为例，功能为**计算addr**后调用**initiateMemRead**方法，并向下传递动态指令类指针
> build/ARM/arch/arm/generated/exec-ns.cc.inc
```
Fault
LDRB64_IMM::initiateAcc(ExecContext *xc,
                            Trace::InstRecord *traceData) const
{
    Addr EA;
    Fault fault = NoFault;

    uint64_t XBase = 0;
    uint8_t Mem = {};
    // 读取base地址寄存器
    XBase = 
    ((xc->readIntRegOperand(this, 0)) & mask(aarch64 ? 64 : 32));
    
    if (baseIsSP && bits(XBase, 3, 0) &&
        SPAlignmentCheckEnabled(xc->tcBas())) {
        return std::make_shared<SPAlignmentFault>();
    }
    //计算地址
    EA = XBase + imm;
    unsigned memAccessFlags = 0|ArmISA::MMU::AllowUnaligned;;

    if (fault == NoFault) {
        fault = initiateMemRead(xc, traceData, EA, Mem, memAccessFlags);
    }

    return fault;
}
```
动态指令信息类有一个initiateMemRead方法，调用了cpu的pushRequest方法，以发送request的方式进行内存读写
> src/cpu/o3/dyn_inst.cc
```
Fault
DynInst::initiateMemRead(Addr addr, unsigned size, Request::Flags flags,
                               const std::vector<bool> &byte_enable)
{
    assert(byte_enable.size() == size);
    return cpu->pushRequest(
        dynamic_cast<DynInstPtr::PtrType>(this),
        /* ld */ true, nullptr, size, addr, flags, nullptr, nullptr,
        byte_enable);
}
```

#### completeAcc函数
调用链：
```
？？？没有找到入口函数
LSQUnit::WritebackEvent::process()
LSQUnit::writeback()
inst->completeAcc();
```

动态指令类的completeAcc实质也是调用了静态指令类的completeACC方法
> src/cpu/o3/dyn_inst.cc
```
Fault
DynInst::completeAcc(PacketPtr pkt)
{
    ...
    fault = staticInst->completeAcc(pkt, this, traceData);
    ...
    return fault;
}
```
以LDRB64_IMM指令类为例子, 其真正调用了动态指令类的setIntRegOperand方法
> build/ARM/arch/arm/generated/exec-ns.cc.inc
```
Fault
LDRB64_IMM::completeAcc(PacketPtr pkt, ExecContext *xc,
                            Trace::InstRecord *traceData) const
{
    Fault fault = NoFault;

    uint64_t WDest = 0;
    uint8_t Mem = {};
    // ARM instructions will not have a pkt if the predicate is false
    getMemLE(pkt, Mem, traceData);

    if (fault == NoFault) {
        WDest = cSwap(Mem, isBigEndian64(xc->tcBase()));
    }

    if (fault == NoFault) {
    {
        uint64_t final_val = WDest;
        
        xc->setIntRegOperand(this, 0, (WDest) & mask(32));
        if (traceData) { traceData->setData(final_val); }
    };
    }
    return fault;
}
```
动态指令类setIntRegOperand方法直接修改cpu寄存器
> src/cpu/o3/dyn_inst.hh
```
void
setIntRegOperand(const StaticInst *si, int idx, RegVal val) override
{
    cpu->setIntReg(renamedDestIdx(idx), val);
    setResult(val);
}
```

## 边缘方法
- 构造函数、析构函数 
- Flag获取函数
  - isMemRef、isLoad、isControl等
- 源、目标寄存器数量获取函数
  - numSrcRegs、numDestRegs、numFPDestRegs、numIntDestRegs、numVecDestRegs、numVecElemDestRegs、numVecPredDestRegs、numCCDestRegs（）
- Flag的get/set函数
  - isMemRef、isLoad、isControl等
  - setFlag、setFirstMicroop等
- 指令类型获取函数
  - opClass
- 源/目标寄存器列表set/get函数
  - destRegIdx、srcRegIdx
  - setDestRegIdx、setSrcRegIdx
- 获取中间产物
  - getEMI（decode过程分为predecode和decode， emi是predecode的产物）
- 生成反汇编函数
  - generateDisassembly
- 获取微指令函数（fetchMicroop）
- 打印Flags函数（printFlags）
- 获取opcode函数（getName）
- 获取经预处理指令函数（getEMI）
- 获取指令类的二进制码（simpleAsBytes、asBytes）