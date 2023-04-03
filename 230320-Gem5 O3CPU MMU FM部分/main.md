## Gem5 O3CPU MMU FM部分

[来自gem5文档](https://www.gem5.org/documentation/general_docs/cpu_models/O3CPU)

O3CPU load指令调用链
```
IEW::tick()->IEW::executeInsts()
  ->LSQUnit::executeLoad()
    ->StaticInst::initiateAcc()
      ->LSQ::pushRequest()
        ->LSQUnit::read()
          ->LSQRequest::buildPackets()
          ->LSQRequest::sendPacketToCache()
    ->LSQUnit::checkViolation()
DcachePort::recvTimingResp()->LSQRequest::recvTimingResp()
  ->LSQUnit::completeDataAccess()
    ->LSQUnit::writeback()
      ->StaticInst::completeAcc()
      ->IEW::instToCommit()
IEW::tick()->IEW::writebackInsts()
```
LSQ::pushRequest() 将分配一个 LSQRequest 来跟踪所有状态，并开始翻译。翻译完成后，它将记录虚拟地址并调用 LSQUnit::read()。
LSQ::pushRequest()的详细调用链
```
LSQ::pushRequest()
->Request::initiateTranslation()
    ->LSQ::SingleDataRequest::initiateTranslation()
        ->LSQ::LSQRequest::sendFragmentToTranslation(int i)
            ->LSQ::sendFragmentToTranslation()
                ->MMU::translateTiming()
                    ->MMU::translateComplete()
                        ->MMU::translateSe
```
在MMU::translateComplete()中定义了delay字段，通过MMU::translateSe计算是否会产生delay。
MMU::translateSe不会赋值delay字段

如果被delay了，LSQ::pushRequest()会被重新触发直到request的delay消除


只有FS模式下，通过translateMmuOn才会计算delay？ translateMmuOn

哪里进行的真正的translate？
src/arch/arm/mmu.cc 在mmu中定义了
MMU::translateSe

在哪里调用的？
```
MMU::translateTiming
->MMU::translateComplete
    ->MMU::translateSe
        ->Process::EmulationPageTable::translate
            ->Process::EmulationPageTable::lookup
                ->EmulationPageTable::find  
```

EmulationPageTable::find若搜索正常，则设置好pAddr return true；否则返回false，在TranslateSe出返回GenericPageTableFault错入

先不考虑MMU::translateFs，先考虑MMU::translateSe

pTable是EmulationPageTable类型
在MMU::translateTiming找不到父调用？




fetch阶段的