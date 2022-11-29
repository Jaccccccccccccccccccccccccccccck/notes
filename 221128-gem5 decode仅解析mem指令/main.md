# gem5 decoder仅解析mem info
由221111-Arm64访存指令指出
>仅以32位的指令字节为输入静态解析，没有当前pc和其他寄存器信息时，无法计算出mem指令信息中的地址
## mem info结构
```
struct mem_info {
    bool is_mem_ref;
    bool is_load;
    bool is_store;
}
```
为何需要同时需要两个变量标识：**is_read** and **is_write**?
- 有些指令为复合操作，即load也store，例如**CASP**指令，其含义是
> **从内存中读取一对 32 位字或 64 位双字，并将它们与保存在第一对寄存器中的值进行比较。如果比较相等，则将第二对寄存器中的值写入内存** [here](https://developer.arm.com/documentation/ddi0602/2021-12/Base-Instructions/CASP--CASPA--CASPAL--CASPL--Compare-and-Swap-Pair-of-words-or-doublewords-in-memory-)


## 代码过程
```
switch (AARCH64) {
    case 0x1:   
    // Aarch64::aarch64(([], {}))
    {
        if (bits(machInst, 27) == 0x0) {
            if (bits(machInst, 28) == 0x0) {
                if (bits(machInst, 31) == 0x0) {
                    switch (bits(machInst, 30, 29)) {
                    case 0x0:
                    case 0x1:
                    case 0x2:
                        return decodeSveInt(machInst);
                    case 0x3:
                        return decodeSveFp(machInst);
                    }
                } else {
                    return decodeSveMem(machInst);
                }
            } else if (bits(machInst, 26) == 0)
                // bit 28:26=100
                return decodeDataProcImm(machInst);
            else
                // bit 28:26=101
                return decodeBranchExcSys(machInst);
        } else if (bits(machInst, 25) == 0) {
            // bit 27=1, 25=0
            return decodeLoadsStores(machInst);
        } else if (bits(machInst, 26) == 0) {
            // bit 27:25=101
            return decodeDataProcReg(machInst);
        } else if (bits(machInst, 24) == 1 &&
                    bits(machInst, 31, 28) == 0xF) {
            return new Gem5Op64(machInst);
        } else {
            // bit 27:25=111
            //switch(decoderFlavor){
            //default:
                return decodeFpAdvSIMD<GenericDecoder>(machInst);
            //}
        }
    }
    break;
    default:
        // Unknown::unknown(([], {}))
        return new MemInfo(-1, -1);
        break;
}
```

中的
- sve部分代码仅保留decodeSveMem分支
- decodeDataProcImm、decodeBranchExcSys分支直接去除
- decodeFpAdvSIMD分支下也需要删除，因为SIMD类的load、store指令在decodeLoadsStores分支下
- Gem5Op64是什么东西？好像是个debug用的指令,删除
- 实现其中的**decodeSveMem**和**decodeLoadsStores**函数
  - decodeSveMemGather32、decodeSveMemGather64和方法中全是load方法
- decodeNeonMem方法在arch/arm/generated/decoder-ns.cc.inc中定义了两次？
  - 93831行的decodeNeonMem方法定义在namespace **Aarch64**中 
  - 97732没有命名空间，


## 结果对比
,对比输出结果没有异常
与gem5 decoder输出的静态指令信息类中的**isMemRef**信息对比，仅decode_mem_info方法没有发现错误，
但发现**某些静态指令信息类中存取指令的isMemRef输出为false**
### 包含指令
- ldp 
- stp
- ldrb
- strb
### 原因
所有isMemRef标识错误的指令都是**宏指令**，宏指令中无需对isMemRef详细标记，因为参与流水线是会被拆分成微指令，在微指令中赋值正确isMemRef即可


