#动态指令信息类

##函数buildInst
fetch阶段静态指令信息类转换动态指令信息类函数
核心操作：构建DynInst
构建参数：
- 当前微指令
- 宏指令
- pc
- next_pc:预测pc
- seq_num uint64_t 指令序列号，用于指令排序
- cpu

```
DynInstPtr
Fetch::buildInst(ThreadID tid, StaticInstPtr staticInst,
        StaticInstPtr curMacroop, const PCStateBase &this_pc,
        const PCStateBase &next_pc, bool trace)
{
    ...
    // 根据静态指令信息类创建一个动态指令信息类
    DynInstPtr instruction = new (arrays) DynInst(
            arrays, staticInst, curMacroop, this_pc, next_pc, seq, cpu);
    instruction->setTid(tid);

    instruction->setThreadState(cpu->thread[tid]);

    // Add instruction to the CPU's list of instructions.
    instruction->setInstListIt(cpu->addInst(instruction));

    // Write the instruction to the first slot in the queue
    // that heads to decode.
    // 写入fetchQueue
    fetchQueue[tid].push_back(instruction);
    ...
    return instruction;
}
```

## 动态指令信息类成员
- seqNum 序列号
- staticInst 普通指令 or 微指令
- macroop 宏指令
- cpu
- thread
- threadNumber
- fault 指令报错的类型
- traceData 指令运行的trace信息 ？
- instResult 指令运行结果，结构是？
- pc PCStateBase 当前指定pc
  - _pc
  - _upc
- predPC 预测下一条指令的pc
- _destMiscRegVal 写回**misc**？ register的值
- _numSrcs 源寄存器数量 来自staticinst
- _numDests 目标寄存器数量 来自staticinst
- RegId *_flatDestIdx 一堆寄存器数据
- PhysRegIdPtr *_destIdx;
- PhysRegIdPtr *_prevDestIdx;
- PhysRegIdPtr *_srcIdx;
- uint8_t *_readySrcIdx;
- readyRegs 源寄存器状态
- effAddr
- physEffAddr
- memReqFlags ？**The memory request flags (from translation).**
- effSize ？ **The size of the request**
- memData  指向数据的指针
- lqIdx ？ load queue index
- lqIt
- sqIdx ？store queue index
- sqIt
- savedRequest 处理TLBmiss的request
- reqToVerify checker
- instListIt ? **Iterator pointing to this BaseDynInst in the list of all insts.**
- - status 指令运行状态
  - 是否在流水线某个阶段
  - 是否已经完成
  - 是否已经计算完成
  - 是否可以commit
  - 是否被squash
  - 是否为线程同步指令
- Inst flags
  - NotAnInst
  - TranslationStarted 宏指令拆分->微指令叫做translation？
  - TranslationCompleted
  - PossibleLoadViolation
  - HitExternalSnoop
  - EffAddrValid  地址检测
  - RecordResult
  - Predicate
  - MemAccPredicate
  - PredTaken
  - IsStrictlyOrdered
  - ReqMade
  - MemOpDone
  - HtmFromTransaction

## 动态指令信息类的部分函数
- DynInst::execute() 
  - 调用了staticInst->execute(this, traceData)函数
  - this是指的当前的dyInst，其实是运行时上下文，包括cpu、thread等
- DynInst::initiateAcc()
  - 调用了staticInst->initiateAcc（this, traceData)
- DynInst::completeAcc(pkt)
  - 调用了staticInst->completeAcc(pkt, this, traceData)

AddImm::execute代码例子
```
Fault
    AddImm::execute(
            ExecContext *xc, Trace::InstRecord *traceData) const
    {
        Fault fault = NoFault;
        uint64_t resTemp = 0;
        resTemp = resTemp;
        uint32_t OptCondCodesNZ = 0;
uint32_t OptCondCodesC = 0;
uint32_t OptCondCodesV = 0;
uint32_t AIWDest = 0;
uint32_t Op1 = 0;
;
        OptCondCodesNZ = xc->readCCRegOperand(this, 1);
OptCondCodesC = xc->readCCRegOperand(this, 2);
OptCondCodesV = xc->readCCRegOperand(this, 3);
Op1 = 
        ((op1 == PCReg) ? readPC(xc) : xc->readIntRegOperand(this, 0))
    ;
;

        if (testPredicate(OptCondCodesNZ, OptCondCodesC, OptCondCodesV, condCode)/*auto*/) {
            AIWDest = resTemp = Op1 + imm;;
            if (fault == NoFault) {
                
        {
            uint32_t final_val = AIWDest;
            
        if (dest == PCReg) {
            bool thumb = THUMB;
            if (thumb) {
                setNextPC(xc, AIWDest);
            } else {
                setIWNextPC(xc, AIWDest);
            }
        } else {
            xc->setIntRegOperand(this, 0, AIWDest);
        }
    ;
            if (traceData) { traceData->setData(final_val); }
        };
            }
        } else {
            xc->setPredicate(false);
        }

        return fault;
    }
```

## 所有函数
动态指令信息类相比于静态指令类，没有增加什么实际函数，都是对状态的修改函数
### 核心函数
- 指令执行函数
  - execute、initiateAcc、completeAcc
- initiateAcc的调用函数（实际上会交给cpu来生成mem访问）
  - initiateMemRead
  - writeMem
  - initiateHtmCmd?
  - initiateMemAMO?
- 计算branch指令跳转地址
  - branchTarget
- trap ？
- demapPage ？

### 边缘函数
- 构造解析函数
- get源/目标寄存器数量
  - numSrcs
  - numDests
  - numSrcRegs
  - numDestRegs
  - numFPDestRegs
  - numIntDestRegs
  - numCCDestRegs
  - numVecDestRegs
  - numVecElemDestRegs
  - numVecPredDestRegs
- 源/目标寄存器列表获取（from 静态指令类）
  - destRegIdx
  - srcRegIdx
- 物理寄存器、逻辑寄存器转换函数
  - flattenedDestIdx
- renamed的物理寄存器获取函数
  - renamedDestIdx
  - renamedSrcIdx
- 映射到同一逻辑寄存器**上一个**物理寄存器
  - prevDestIdx
- 源寄存器准备状态,get/set函数
  - readySrcIdx
  - markSrcRegReady
- Flag get/set函数
  - recordResult
  - effAddrValid
  - memOpDone
  - notAnInst
  - setNotAnInst
  - translationStarted
  - translationCompleted
  - possibleLoadViolation
  - hitExternalSnoop
  - isTranslationDelayed
  - readPredTaken/setPredTaken
  - getHtmTransactionalDepth
  - setHtmTransactionalState
  - readMemAccPredicate/setMemAccPredicate
  - readPredicate/setPredicate
  - strictlyOrdered
  - hasRequest
- dump函数
  - dump
- 获取cpuid
  - cpuId
- 获取cpu的socketId
  - socketId
- 获取cpu的dataRequestorId
  - requestorId
- 获取contextId
  - contextId
- 获取出错类型
  - getFault
- 是否已经计算return回到的指令
  - doneTargCalc
- 预测地址 set/get函数
  - setPredTarg
  - readPredTarg
- **一堆**指令类型flags
  - 来自于静态指令类，isNop等
- 获取静态指令类的opclass
  - opClass
- htm事务id get/set
  - getHtmTransactionUid
  - newHtmTransactionUid
  - clearHtmTransactionalState
- 事务depth
  - getHtmTransactionalDepth
- serialize相关函数
  - setSerializeBefore
  - clearSerializeBefore
  - isTempSerializeBefore
  - setSerializeAfter
  - clearSerializeAfter
  - isTempSerializeAfter
  - setSerializeHandled
  - isSerializeHandled
- 指令status get/set函数
  - setCompleted/isCompleted
  - setResultReady/isResultReady
  - setCanIssue/readyToIssue
  - clearCanIssue/setIssued
  - isIssued/clearIssued
  - setExecuted/isExecuted
  - setCanCommit/clearCanCommit/setCommitted/isCommitted
  - readyToCommit/setAtCommit/isAtCommit
  - setSquashed/isSquashed
  - setInIQ/clearInIQ/isInIQ
  - isSquashedInIQ/setSquashedInIQ
  - setInLSQ/removeInLSQ/isInLSQ
  - setSquashedInLSQ/isSquashedInLSQ
  - setInROB/clearInROB/isInROB
  - setSquashedInROB/isSquashedInROB/isPinnedRegsRenamed
  - setPinnedRegsRenamed/isPinnedRegsWritten/setPinnedRegsWritten
  - setPinnedRegsSquashDone/isPinnedRegsSquashDone
  - setSerializeBefore/clearSerializeBefore
  - setSerializeAfter/clearSerializeAfter
  - setSerializeHandled/isSerializeHandled
- 当前pc get/set
  - pcState
- 当前线程state set函数
  - setTid setThreadState
- 获取当前线程状态（thread context）
  - tcBase
- 指令列表get set
  - getInstListIt/setInstListIt
- 获取连续store条件失败 set get
  - readStCondFailures、setStCondFailures
- monitor mwait functions？
  - armMonitor
  - mwait
  - mwaitAtomic
  - getAddrMonitor
- msic register操作 ？？？ msic是什么
  - readMiscReg/setMiscReg/readMiscRegOperand/setMiscRegOperand/updateMiscRegs
- 物理寄存器 set get
  - readIntRegOperand
  - readFloatRegOperandBits
  - readVecRegOperand
  - getWritableVecRegOperand
  - readVecElemOperand
  - readVecPredRegOperand
  - getWritableVecPredRegOperand
  - readCCRegOperand
  - setIntRegOperand
  - setFloatRegOperandBits
  - setVecRegOperand
  - setVecElemOperand
  - setVecPredRegOperand
  - setCCRegOperand
- 重命名 
  - renameDestReg
  - renameSrcReg
- 判断是否mispredicted
- 指令结果get/set函数
  - popResult
  - setResult
- 物理寄存器实际赋值？ iew阶段调用
  - forwardOldRegs