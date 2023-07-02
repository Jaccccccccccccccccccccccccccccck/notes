gem5 debug输出以查看fs启动的操作是什么

```
M5_PATH=/home/ build/ARM/gem5.opt \
--outdir=/home/test_o3_l3_classic/ \
--debug-flags=All \
configs/example/fs.py \
--cpu-type=AtomicSimpleCPU \
--mem-size=8GB \
-n1 \
--bootloader=/home/binaries/boot.arm64 \
--disk-image=ubuntu-18.04-arm64-docker-add-spec.img \
--kernel=vmlinux-4.14 \
--caches \
> gem5_debug.out
```

首先是解析了第一个elf文件，arch/arm64/kernel/head.o 
```
Global frequency set at 1000000000000 ticks per second
      0: system.clk_domain: Setting clock period to 1000 ticks for source clock system.clk_domain
      0: system.mem_ctrls.dram: Setting up DRAM Interface
      0: system.mem_ctrls.dram: Creating DRAM rank 0 
      0: system.mem_ctrls.dram: Creating DRAM rank 1 
      0: system.mem_ctrls.dram: Memory capacity 8589934592 (8589934592) bytes
      0: system.mem_ctrls.dram: Row buffer size 8192 bytes with 128 bursts per row buffer
0: 0xffffffc000080000 8310040
0(uninitialized): 0xffffffc00086cd18 245684
      0: global: Found Symbol Table, 98219 symbols present.      0: global: Symbol: arch/arm64/kernel/head.o                 value 0.
      0: global: Symbol: __reg_num_x0                             value 0.
      0: global: Symbol: __reg_num_x1                             value 0x1.
      0: global: Symbol: __reg_num_x2                             value 0x2.
      0: global: Symbol: __reg_num_x3                             value 0x3.
      0: global: Symbol: __reg_num_x4                             value 0x4.
      0: global: Symbol: __reg_num_x5                             value 0x5.
      0: global: Symbol: __reg_num_x6                             value 0x6.
      0: global: Symbol: __reg_num_x7                             value 0x7.
      0: global: Symbol: __reg_num_x8                             value 0x8.
      ...
```

直到
```
   46956       0: system.physmem: Creating backing store for range [0:0x4000000] with size 67108864
   46957       0: system.physmem: Mapping memory system.realview.bootmem to backing store
   46958       0: system.physmem: Creating backing store for range [0x4000000:0x4040000] with size 262144
   46959       0: system.physmem: Mapping memory system.realview.trusted_sram to backing store
   46960       0: system.physmem: Creating backing store for range [0x6000000:0x8000000] with size 33554432
   46961       0: system.physmem: Mapping memory system.realview.trusted_dram to backing store
   46962       0: system.physmem: Creating backing store for range [0x8000000:0xc000000] with size 67108864
   46963       0: system.physmem: Mapping memory system.realview.flash0 to backing store
   46964       0: system.physmem: Creating backing store for range [0xc000000:0x10000000] with size 67108864
   46965       0: system.physmem: Mapping memory system.realview.flash1 to backing store
   46966       0: system.physmem: Creating backing store for range [0x18000000:0x1a000000] with size 33554432
   46967       0: system.physmem: Mapping memory system.realview.vram to backing store
   46968       0: system.physmem: Creating backing store for range [0x2e000000:0x2e008000] with size 32768
   46969       0: system.physmem: Mapping memory system.realview.non_trusted_sram to backing store
   46970       0: system.physmem: Creating backing store for range [0x80000000:0x280000000] with size 8589934592
   46971       0: system.physmem: Mapping memory system.mem_ctrls.dram to backing store
   46972       0: system.cpu_clk_domain: Setting clock period to 500 ticks for source clock system.cpu_clk_domain
   46973       0: system.cpu.interrupts: Interrupts all cleared
   46974       0: system.cpu: Constructing CPU with id 0, socket id 0
   46975       0: system.mem_ctrls: Setting up controller
   46976       0: system.realview.pci_host: 00:01.0: Registering device
   46977       0: system.realview.clock24MHz: Setting clock period to 41667 ticks for source clock system.realview.clock24MHz
   46978       0: system.realview.clock32KHz: Setting clock period to 31250000 ticks for source clock system.realview.clock32KHz
   46979       0: system.realview.gic: cpuEnabled[0]=0 cpuEnabled[1]=0
   46980       0: system.vncserver: Vnc server created at port 5900
   46981       0: system.realview.uart1.device: : can't bind address terminal port 3456 inuse PID 29535
   46982       0: system.realview.uart2.device: : can't bind address terminal port 3456 inuse PID 29535
   46983       0: system.realview.uart2.device: : can't bind address terminal port 3457 inuse PID 29535
   46984       0: system.realview.uart3.device: : can't bind address terminal port 3456 inuse PID 29535
      46985       0: system.realview.uart3.device: : can't bind address terminal port 3457 inuse PID 29535
   46986       0: system.realview.uart3.device: : can't bind address terminal port 3458 inuse PID 29535
   46987       0: system.membus: Received range change from cpu_side_ports system.bridge.cpu_side_port
   46988       0: system.membus: Adding range [0xc000000:0x20000000] for id 0
   46989       0: system.membus: Adding range [0x2f000000:0x80000000] for id 0
   46990       0: system.iobus: Received range change from cpu_side_ports system.iocache.cpu_side_port
   46991       0: system.iobus: Adding range [0x80000000:0x280000000] for id 17
   46992       0: system.membus: Received range change from cpu_side_ports system.mem_ctrls.port
   46993       0: system.mem_ctrls.port: Pushing DRAM ranges to port
   46994       0: system.membus: Adding range [0x80000000:0x280000000] for id 15
   46995       0: system.membus: Adding snooping requestor system.iocache.mem_side_port
   46996       0: system.membus: Adding snooping requestor system.cpu.icache.mem_side_port
   46997       0: system.membus: Adding snooping requestor system.cpu.dcache.mem_side_port
   46998       0: system.membus: Received range change from cpu_side_ports system.membus.badaddr_responder.pio
   46999       0: system.iobus: Received range change from cpu_side_ports system.pci_ide.pio
   47000       0: system.membus: Received range change from cpu_side_ports system.realview.bootmem.port
   47001       0: system.membus: Adding range [0:0x4000000] for id 1
   47002       0: system.membus: Received range change from cpu_side_ports system.realview.el2_watchdog.pio
   47003       0: system.membus: Adding range [0x2a450000:0x2a460000] for id 7
   47004       0: system.membus: Adding range [0x2a440000:0x2a450000] for id 7
   47005       0: system.iobus: Received range change from cpu_side_ports system.realview.energy_ctrl.pio
   47006       0: system.realview.energy_ctrl: registering range: 0x10000000-0x2c
   47007       0: system.iobus: Adding range [0x10000000:0x1000002c] for id 8
   47008       0: system.membus: Received range change from cpu_side_ports system.realview.flash0.port
   47009       0: system.membus: Adding range [0x8000000:0xc000000] for id 5
   47010       0: system.iobus: Received range change from cpu_side_ports system.realview.flash1.port
   47011       0: system.iobus: Adding range [0xc000000:0x10000000] for id 0
   47012       0: system.membus: Received range change from cpu_side_ports system.realview.generic_timer_mem.pio
   47013       0: system.membus: Adding range [0x2a430000:0x2a431000] for id 6
   47014       0: system.membus: Adding range [0x2a800000:0x2a801000] for id 6
   47015       0: system.membus: Adding range [0x2a810000:0x2a811000] for id 6
   47016       0: system.membus: Received range change from cpu_side_ports system.realview.generic_timer_mem.frames0.pio
   47017       0: system.membus: Adding range [0x2a820000:0x2a821000] for id 10
   47018       0: system.membus: Received range change from cpu_side_ports system.realview.generic_timer_mem.frames1.pio
   47019       0: system.membus: Adding range [0x2a830000:0x2a831000] for id 11
   47020       0: system.membus: Received range change from cpu_side_ports system.realview.gic.pio
   47021       0: system.membus: Adding range [0x2c001000:0x2c002000] for id 12
   47022       0: system.membus: Adding range [0x2c002000:0x2c004000] for id 12
   47023       0: system.membus: Received range change from cpu_side_ports system.realview.gicv2m.pio
   47024       0: system.membus: Adding range [0x2c1c0000:0x2c1d0000] for id 14
      47025       0: system.iobus: Received range change from cpu_side_ports system.realview.kmi0.pio
   47026       0: system.realview.kmi0: registering range: 0x1c060000-0x1000
   47027       0: system.iobus: Adding range [0x1c060000:0x1c061000] for id 3
   47028       0: system.iobus: Received range change from cpu_side_ports system.realview.kmi1.pio
   47029       0: system.realview.kmi1: registering range: 0x1c070000-0x1000
   47030       0: system.iobus: Adding range [0x1c070000:0x1c071000] for id 4
   47031       0: system.membus: Received range change from cpu_side_ports system.realview.non_trusted_sram.port
   47032       0: system.membus: Adding range [0x2e000000:0x2e008000] for id 4
   47033       0: system.iobus: Received range change from cpu_side_ports system.realview.pci_host.pio
   47034       0: system.iobus: Adding range [0x30000000:0x40000000] for id 7
   47035       0: system.iobus: Received range change from cpu_side_ports system.realview.pwr_ctrl.pio
   47036       0: system.realview.pwr_ctrl: registering range: 0x1c100000-0x1000
   47037       0: system.iobus: Adding range [0x1c100000:0x1c101000] for id 9
   47038       0: system.iobus: Received range change from cpu_side_ports system.realview.realview_io.pio
   47039       0: system.realview.realview_io: registering range: 0x1c010000-0xd4
   47040       0: system.iobus: Adding range [0x1c010000:0x1c0100d4] for id 2
   47041       0: system.iobus: Received range change from cpu_side_ports system.realview.rtc.pio
   47042       0: system.realview.rtc: registering range: 0x1c170000-0x1000
   47043       0: system.iobus: Adding range [0x1c170000:0x1c171000] for id 6
   47044       0: system.membus: Received range change from cpu_side_ports system.realview.system_watchdog.pio
   47045       0: system.realview.system_watchdog: registering range: 0x2b060000-0x1000
   47046       0: system.membus: Adding range [0x2b060000:0x2b061000] for id 9
   47047       0: system.membus: Received range change from cpu_side_ports system.realview.trusted_dram.port
   47048       0: system.membus: Adding range [0x6000000:0x8000000] for id 3
   47049       0: system.membus: Received range change from cpu_side_ports system.realview.trusted_sram.port
   47050       0: system.membus: Adding range [0x4000000:0x4040000] for id 2
   47051       0: system.membus: Received range change from cpu_side_ports system.realview.trusted_watchdog.pio
   47052       0: system.realview.trusted_watchdog: registering range: 0x2a490000-0x1000
   47053       0: system.membus: Adding range [0x2a490000:0x2a491000] for id 8
   47054       0: system.iobus: Received range change from cpu_side_ports system.realview.uart0.pio
   47055       0: system.realview.uart0: registering range: 0x1c090000-0x1000
   47056       0: system.iobus: Adding range [0x1c090000:0x1c091000] for id 12
   47057       0: system.iobus: Received range change from cpu_side_ports system.realview.uart1.pio
   47058       0: system.realview.uart1: registering range: 0x1c0a0000-0x1000
   47059       0: system.iobus: Adding range [0x1c0a0000:0x1c0a1000] for id 13
   47060       0: system.iobus: Received range change from cpu_side_ports system.realview.uart2.pio
   47061       0: system.realview.uart2: registering range: 0x1c0b0000-0x1000
   47062       0: system.iobus: Adding range [0x1c0b0000:0x1c0b1000] for id 14
   47063       0: system.iobus: Received range change from cpu_side_ports system.realview.uart3.pio
   47064       0: system.realview.uart3: registering range: 0x1c0c0000-0x1000
      47065       0: system.iobus: Adding range [0x1c0c0000:0x1c0c1000] for id 15
   47066       0: system.membus: Received range change from cpu_side_ports system.realview.vgic.pio
   47067       0: system.membus: Got address ranges from all responders
   47068       0: system.membus: Adding range [0x2c004000:0x2c006000] for id 13
   47069       0: system.membus: Adding range [0x2c006000:0x2c008000] for id 13
   47070       0: system.membus: Aggregating address ranges
   47071       0: system.membus: -- Adding range [0:0x4000000]
   47072       0: system.membus: -- Adding range [0x4000000:0x4040000]
   47073       0: system.membus: -- Adding range [0x6000000:0x8000000]
   47074       0: system.membus: -- Adding range [0x8000000:0xc000000]
   47075       0: system.membus: -- Adding range [0xc000000:0x20000000]
   47076       0: system.membus: -- Adding range [0x2a430000:0x2a431000]
   47077       0: system.membus: -- Adding range [0x2a440000:0x2a450000]
   47078       0: system.membus: -- Adding range [0x2a450000:0x2a460000]
   47079       0: system.membus: -- Adding range [0x2a490000:0x2a491000]
   47080       0: system.membus: -- Adding range [0x2a800000:0x2a801000]
   47081       0: system.membus: -- Adding range [0x2a810000:0x2a811000]
   47082       0: system.membus: -- Adding range [0x2a820000:0x2a821000]
   47083       0: system.membus: -- Adding range [0x2a830000:0x2a831000]
   47084       0: system.membus: -- Adding range [0x2b060000:0x2b061000]
   47085       0: system.membus: -- Adding range [0x2c001000:0x2c002000]
   47086       0: system.membus: -- Adding range [0x2c002000:0x2c004000]
   47087       0: system.membus: -- Adding range [0x2c004000:0x2c006000]
   47088       0: system.membus: -- Adding range [0x2c006000:0x2c008000]
   47089       0: system.membus: -- Adding range [0x2c1c0000:0x2c1d0000]
   47090       0: system.membus: -- Adding range [0x2e000000:0x2e008000]
   47091       0: system.membus: -- Adding range [0x2f000000:0x80000000]
   47092       0: system.membus: -- Adding range [0x80000000:0x280000000]
   47093       0: system.iobus: Received range change from cpu_side_ports system.realview.vio0.pio
   47094       0: system.realview.vio0: registering range: 0x1c130000-0x1000
   47095       0: system.iobus: Adding range [0x1c130000:0x1c131000] for id 10
   47096       0: system.iobus: Received range change from cpu_side_ports system.realview.vio1.pio
   47097       0: system.realview.vio1: registering range: 0x1c140000-0x1000
   47098       0: system.iobus: Adding range [0x1c140000:0x1c141000] for id 11
   47099       0: system.iobus: Received range change from cpu_side_ports system.realview.vram.port
   47100       0: system.iobus: Adding range [0x18000000:0x1a000000] for id 1
   47101       0: system.iobus: Received range change from cpu_side_ports system.realview.watchdog.pio
   47102       0: system.iobus: Got address ranges from all responders
   47103       0: system.realview.watchdog: registering range: 0x1c0f0000-0x1000
   47104       0: system.iobus: Adding range [0x1c0f0000:0x1c0f1000] for id 5
      47105       0: system.iobus: Aggregating address ranges
   47106       0: system.iobus: -- Adding range [0xc000000:0x10000000]
   47107       0: system.iobus: -- Adding range [0x10000000:0x1000002c]
   47108       0: system.iobus: -- Adding range [0x18000000:0x1a000000]
   47109       0: system.iobus: -- Adding range [0x1c010000:0x1c0100d4]
   47110       0: system.iobus: -- Adding range [0x1c060000:0x1c061000]
   47111       0: system.iobus: -- Adding range [0x1c070000:0x1c071000]
   47112       0: system.iobus: -- Adding range [0x1c090000:0x1c091000]
   47113       0: system.iobus: -- Adding range [0x1c0a0000:0x1c0a1000]
   47114       0: system.iobus: -- Adding range [0x1c0b0000:0x1c0b1000]
   47115       0: system.iobus: -- Adding range [0x1c0c0000:0x1c0c1000]
   47116       0: system.iobus: -- Adding range [0x1c0f0000:0x1c0f1000]
   47117       0: system.iobus: -- Adding range [0x1c100000:0x1c101000]
   47118       0: system.iobus: -- Adding range [0x1c130000:0x1c131000]
   47119       0: system.iobus: -- Adding range [0x1c140000:0x1c141000]
   47120       0: system.iobus: -- Adding range [0x1c170000:0x1c171000]
   47121       0: system.iobus: -- Adding range [0x30000000:0x40000000]
   47122       0: system.iobus: -- Adding range [0x80000000:0x280000000]
   47123       0: global: root: regStats in group system
   47124       0: global: system: regStats in group bridge
   47125       0: global: system.bridge: regStats in group power_state
   47126       0: global: system: regStats in group clk_domain
   47127       0: global: system: regStats in group cpu
   47128       0: global: system.cpu: regStats in group dcache
   47129       0: global: system.cpu.dcache: regStats in group BadAddressError
   47130       0: global: system.cpu.dcache: regStats in group CleanEvict
   47131       0: global: system.cpu.dcache: regStats in group CleanInvalidReq
   47132       0: global: system.cpu.dcache: regStats in group CleanInvalidResp
   47133       0: global: system.cpu.dcache: regStats in group CleanSharedReq
   47134       0: global: system.cpu.dcache: regStats in group CleanSharedResp
   47135       0: global: system.cpu.dcache: regStats in group Deprecated_MessageReq
   47136       0: global: system.cpu.dcache: regStats in group Deprecated_MessageResp
   47137       0: global: system.cpu.dcache: regStats in group FlushReq
   47138       0: global: system.cpu.dcache: regStats in group FunctionalReadError
   47139       0: global: system.cpu.dcache: regStats in group FunctionalWriteError
   47140       0: global: system.cpu.dcache: regStats in group HTMAbort
   47141       0: global: system.cpu.dcache: regStats in group HTMReq
   47142       0: global: system.cpu.dcache: regStats in group HTMReqResp
   47143       0: global: system.cpu.dcache: regStats in group HardPFReq
   47144       0: global: system.cpu.dcache: regStats in group HardPFResp
      47145       0: global: system.cpu.dcache: regStats in group InvalidCmd
   47146       0: global: system.cpu.dcache: regStats in group InvalidDestError
   47147       0: global: system.cpu.dcache: regStats in group InvalidateReq
   47148       0: global: system.cpu.dcache: regStats in group InvalidateResp
   47149       0: global: system.cpu.dcache: regStats in group LoadLockedReq
   47150       0: global: system.cpu.dcache: regStats in group MemFenceReq
   47151       0: global: system.cpu.dcache: regStats in group MemFenceResp
   47152       0: global: system.cpu.dcache: regStats in group MemSyncReq
   47153       0: global: system.cpu.dcache: regStats in group MemSyncResp
   47154       0: global: system.cpu.dcache: regStats in group PrintReq
   47155       0: global: system.cpu.dcache: regStats in group ReadCleanReq
   47156       0: global: system.cpu.dcache: regStats in group ReadExReq
   47157       0: global: system.cpu.dcache: regStats in group ReadExResp
   47158       0: global: system.cpu.dcache: regStats in group ReadReq
   47159       0: global: system.cpu.dcache: regStats in group ReadResp
   47160       0: global: system.cpu.dcache: regStats in group ReadRespWithInvalidate
   47161       0: global: system.cpu.dcache: regStats in group ReadSharedReq
   47162       0: global: system.cpu.dcache: regStats in group SCUpgradeFailReq
   47163       0: global: system.cpu.dcache: regStats in group SCUpgradeReq
   47164       0: global: system.cpu.dcache: regStats in group SoftPFExReq
   47165       0: global: system.cpu.dcache: regStats in group SoftPFReq
   47166       0: global: system.cpu.dcache: regStats in group SoftPFResp
   47167       0: global: system.cpu.dcache: regStats in group StoreCondFailReq
   47168       0: global: system.cpu.dcache: regStats in group StoreCondReq
   47169       0: global: system.cpu.dcache: regStats in group StoreCondResp
   47170       0: global: system.cpu.dcache: regStats in group SwapReq
   47171       0: global: system.cpu.dcache: regStats in group SwapResp
   47172       0: global: system.cpu.dcache: regStats in group UpgradeFailResp
   47173       0: global: system.cpu.dcache: regStats in group UpgradeReq
   47174       0: global: system.cpu.dcache: regStats in group UpgradeResp
   47175       0: global: system.cpu.dcache: regStats in group WriteClean
   47176       0: global: system.cpu.dcache: regStats in group WriteCompleteResp
   47177       0: global: system.cpu.dcache: regStats in group WriteLineReq
   47178       0: global: system.cpu.dcache: regStats in group WriteReq
   47179       0: global: system.cpu.dcache: regStats in group WriteResp
   47180       0: global: system.cpu.dcache: regStats in group WritebackClean
   47181       0: global: system.cpu.dcache: regStats in group WritebackDirty
   47182       0: global: system.cpu.dcache: regStats in group power_state
   47183       0: global: system.cpu.dcache: regStats in group replacement_policy
   47184       0: global: system.cpu.dcache: regStats in group tags
      47185       0: global: system.cpu.dcache.tags: regStats in group indexing_policy
   47186       0: global: system.cpu.dcache.tags: regStats in group power_state
   47187       0: global: system.cpu: regStats in group decoder
   47188       0: global: system.cpu: regStats in group exec_context.thread_0
   47189       0: global: system.cpu: regStats in group icache
   47190       0: global: system.cpu.icache: regStats in group BadAddressError
   47191       0: global: system.cpu.icache: regStats in group CleanEvict
   47192       0: global: system.cpu.icache: regStats in group CleanInvalidReq
   47193       0: global: system.cpu.icache: regStats in group CleanInvalidResp
   47194       0: global: system.cpu.icache: regStats in group CleanSharedReq
   47195       0: global: system.cpu.icache: regStats in group CleanSharedResp
   47196       0: global: system.cpu.icache: regStats in group Deprecated_MessageReq
   47197       0: global: system.cpu.icache: regStats in group Deprecated_MessageResp
   47198       0: global: system.cpu.icache: regStats in group FlushReq
   47199       0: global: system.cpu.icache: regStats in group FunctionalReadError
   47200       0: global: system.cpu.icache: regStats in group FunctionalWriteError
   47201       0: global: system.cpu.icache: regStats in group HTMAbort
   47202       0: global: system.cpu.icache: regStats in group HTMReq
   47203       0: global: system.cpu.icache: regStats in group HTMReqResp
   47204       0: global: system.cpu.icache: regStats in group HardPFReq
   47205       0: global: system.cpu.icache: regStats in group HardPFResp
   47206       0: global: system.cpu.icache: regStats in group InvalidCmd
   47207       0: global: system.cpu.icache: regStats in group InvalidDestError
   47208       0: global: system.cpu.icache: regStats in group InvalidateReq
   47209       0: global: system.cpu.icache: regStats in group InvalidateResp
   47210       0: global: system.cpu.icache: regStats in group LoadLockedReq
   47211       0: global: system.cpu.icache: regStats in group MemFenceReq
   47212       0: global: system.cpu.icache: regStats in group MemFenceResp
   47213       0: global: system.cpu.icache: regStats in group MemSyncReq
   47214       0: global: system.cpu.icache: regStats in group MemSyncResp
   47215       0: global: system.cpu.icache: regStats in group PrintReq
   47216       0: global: system.cpu.icache: regStats in group ReadCleanReq
   47217       0: global: system.cpu.icache: regStats in group ReadExReq
   47218       0: global: system.cpu.icache: regStats in group ReadExResp
   47219       0: global: system.cpu.icache: regStats in group ReadReq
   47220       0: global: system.cpu.icache: regStats in group ReadResp
   47221       0: global: system.cpu.icache: regStats in group ReadRespWithInvalidate
   47222       0: global: system.cpu.icache: regStats in group ReadSharedReq
   47223       0: global: system.cpu.icache: regStats in group SCUpgradeFailReq
   47224       0: global: system.cpu.icache: regStats in group SCUpgradeReq
      47225       0: global: system.cpu.icache: regStats in group SoftPFExReq
   47226       0: global: system.cpu.icache: regStats in group SoftPFReq
   47227       0: global: system.cpu.icache: regStats in group SoftPFResp
   47228       0: global: system.cpu.icache: regStats in group StoreCondFailReq
   47229       0: global: system.cpu.icache: regStats in group StoreCondReq
   47230       0: global: system.cpu.icache: regStats in group StoreCondResp
   47231       0: global: system.cpu.icache: regStats in group SwapReq
   47232       0: global: system.cpu.icache: regStats in group SwapResp
   47233       0: global: system.cpu.icache: regStats in group UpgradeFailResp
   47234       0: global: system.cpu.icache: regStats in group UpgradeReq
   47235       0: global: system.cpu.icache: regStats in group UpgradeResp
   47236       0: global: system.cpu.icache: regStats in group WriteClean
   47237       0: global: system.cpu.icache: regStats in group WriteCompleteResp
   47238       0: global: system.cpu.icache: regStats in group WriteLineReq
   47239       0: global: system.cpu.icache: regStats in group WriteReq
   47240       0: global: system.cpu.icache: regStats in group WriteResp
   47241       0: global: system.cpu.icache: regStats in group WritebackClean
   47242       0: global: system.cpu.icache: regStats in group WritebackDirty
   47243       0: global: system.cpu.icache: regStats in group power_state
   47244       0: global: system.cpu.icache: regStats in group replacement_policy
   47245       0: global: system.cpu.icache: regStats in group tags
   47246       0: global: system.cpu.icache.tags: regStats in group indexing_policy
   47247       0: global: system.cpu.icache.tags: regStats in group power_state
   47248       0: global: system.cpu: regStats in group interrupts
   47249       0: global: system.cpu: regStats in group isa
   47250       0: global: system.cpu.isa: regStats in group release_se
   47251       0: global: system.cpu: regStats in group mmu
   47252       0: global: system.cpu.mmu: regStats in group dtb
   47253       0: global: system.cpu.mmu: regStats in group dtb_walker
   47254       0: global: system.cpu.mmu.dtb_walker: regStats in group power_state
   47255       0: global: system.cpu.mmu: regStats in group itb
   47256       0: global: system.cpu.mmu: regStats in group itb_walker
   47257       0: global: system.cpu.mmu.itb_walker: regStats in group power_state
   47258       0: global: system.cpu.mmu: regStats in group l2_shared
   47259       0: global: system.cpu.mmu: regStats in group stage2_dtb
   47260       0: global: system.cpu.mmu: regStats in group stage2_dtb_walker
   47261       0: global: system.cpu.mmu.stage2_dtb_walker: regStats in group power_state
   47262       0: global: system.cpu.mmu: regStats in group stage2_itb
   47263       0: global: system.cpu.mmu: regStats in group stage2_itb_walker
   47264       0: global: system.cpu.mmu.stage2_itb_walker: regStats in group power_state
      47265       0: global: system.cpu: regStats in group power_state
   47266       0: global: system.cpu: regStats in group thread_0
   47267       0: global: system.cpu: regStats in group tracer
   47268       0: global: system: regStats in group cpu_clk_domain
   47269       0: global: system: regStats in group cpu_voltage_domain
   47270       0: global: system: regStats in group dvfs_handler
   47271       0: global: system: regStats in group iobus
   47272       0: global: system.iobus: regStats in group power_state
   47273       0: global: system.iobus: regStats in group reqLayer0
   47274       0: global: system.iobus: regStats in group reqLayer1
   47275       0: global: system.iobus: regStats in group reqLayer10
   47276       0: global: system.iobus: regStats in group reqLayer11
   47277       0: global: system.iobus: regStats in group reqLayer12
   47278       0: global: system.iobus: regStats in group reqLayer13
   47279       0: global: system.iobus: regStats in group reqLayer14
   47280       0: global: system.iobus: regStats in group reqLayer15
   47281       0: global: system.iobus: regStats in group reqLayer16
   47282       0: global: system.iobus: regStats in group reqLayer17
   47283       0: global: system.iobus: regStats in group reqLayer2
   47284       0: global: system.iobus: regStats in group reqLayer3
   47285       0: global: system.iobus: regStats in group reqLayer4
   47286       0: global: system.iobus: regStats in group reqLayer5
   47287       0: global: system.iobus: regStats in group reqLayer6
   47288       0: global: system.iobus: regStats in group reqLayer7
   47289       0: global: system.iobus: regStats in group reqLayer8
   47290       0: global: system.iobus: regStats in group reqLayer9
   47291       0: global: system.iobus: regStats in group respLayer0
   47292       0: global: system.iobus: regStats in group respLayer1
   47293       0: global: system: regStats in group iocache
   47294       0: global: system.iocache: regStats in group BadAddressError
   47295       0: global: system.iocache: regStats in group CleanEvict
   47296       0: global: system.iocache: regStats in group CleanInvalidReq
   47297       0: global: system.iocache: regStats in group CleanInvalidResp
   47298       0: global: system.iocache: regStats in group CleanSharedReq
   47299       0: global: system.iocache: regStats in group CleanSharedResp
   47300       0: global: system.iocache: regStats in group Deprecated_MessageReq
   47301       0: global: system.iocache: regStats in group Deprecated_MessageResp
   47302       0: global: system.iocache: regStats in group FlushReq
   47303       0: global: system.iocache: regStats in group FunctionalReadError
   47304       0: global: system.iocache: regStats in group FunctionalWriteError
      47305       0: global: system.iocache: regStats in group HTMAbort
   47306       0: global: system.iocache: regStats in group HTMReq
   47307       0: global: system.iocache: regStats in group HTMReqResp
   47308       0: global: system.iocache: regStats in group HardPFReq
   47309       0: global: system.iocache: regStats in group HardPFResp
   47310       0: global: system.iocache: regStats in group InvalidCmd
   47311       0: global: system.iocache: regStats in group InvalidDestError
   47312       0: global: system.iocache: regStats in group InvalidateReq
   47313       0: global: system.iocache: regStats in group InvalidateResp
   47314       0: global: system.iocache: regStats in group LoadLockedReq
   47315       0: global: system.iocache: regStats in group MemFenceReq
   47316       0: global: system.iocache: regStats in group MemFenceResp
   47317       0: global: system.iocache: regStats in group MemSyncReq
   47318       0: global: system.iocache: regStats in group MemSyncResp
   47319       0: global: system.iocache: regStats in group PrintReq
   47320       0: global: system.iocache: regStats in group ReadCleanReq
   47321       0: global: system.iocache: regStats in group ReadExReq
   47322       0: global: system.iocache: regStats in group ReadExResp
   47323       0: global: system.iocache: regStats in group ReadReq
   47324       0: global: system.iocache: regStats in group ReadResp
   47325       0: global: system.iocache: regStats in group ReadRespWithInvalidate
   47326       0: global: system.iocache: regStats in group ReadSharedReq
   47327       0: global: system.iocache: regStats in group SCUpgradeFailReq
   47328       0: global: system.iocache: regStats in group SCUpgradeReq
   47329       0: global: system.iocache: regStats in group SoftPFExReq
   47330       0: global: system.iocache: regStats in group SoftPFReq
   47331       0: global: system.iocache: regStats in group SoftPFResp
   47332       0: global: system.iocache: regStats in group StoreCondFailReq
   47333       0: global: system.iocache: regStats in group StoreCondReq
   47334       0: global: system.iocache: regStats in group StoreCondResp
   47335       0: global: system.iocache: regStats in group SwapReq
   47336       0: global: system.iocache: regStats in group SwapResp
   47337       0: global: system.iocache: regStats in group UpgradeFailResp
   47338       0: global: system.iocache: regStats in group UpgradeReq
   47339       0: global: system.iocache: regStats in group UpgradeResp
   47340       0: global: system.iocache: regStats in group WriteClean
   47341       0: global: system.iocache: regStats in group WriteCompleteResp
   47342       0: global: system.iocache: regStats in group WriteLineReq
   47343       0: global: system.iocache: regStats in group WriteReq
   47344       0: global: system.iocache: regStats in group WriteResp
      47345       0: global: system.iocache: regStats in group WritebackClean
   47346       0: global: system.iocache: regStats in group WritebackDirty
   47347       0: global: system.iocache: regStats in group power_state
   47348       0: global: system.iocache: regStats in group replacement_policy
   47349       0: global: system.iocache: regStats in group tags
   47350       0: global: system.iocache.tags: regStats in group indexing_policy
   47351       0: global: system.iocache.tags: regStats in group power_state
   47352       0: global: system: regStats in group mem_ctrls
   47353       0: global: system.mem_ctrls: regStats in group dram
   47354       0: global: system.mem_ctrls.dram: regStats in group power_state
   47355       0: global: system.mem_ctrls.dram: regStats in group rank0
   47356       0: global: system.mem_ctrls.dram: regStats in group rank1
   47357       0: global: system.mem_ctrls: regStats in group power_state
   47358       0: global: system: regStats in group membus
   47359       0: global: system.membus: regStats in group badaddr_responder
   47360       0: global: system.membus.badaddr_responder: regStats in group power_state
   47361       0: global: system.membus: regStats in group power_state
   47362       0: global: system.membus: regStats in group reqLayer0
   47363       0: global: system.membus: regStats in group reqLayer1
   47364       0: global: system.membus: regStats in group reqLayer10
   47365       0: global: system.membus: regStats in group reqLayer11
   47366       0: global: system.membus: regStats in group reqLayer12
   47367       0: global: system.membus: regStats in group reqLayer13
   47368       0: global: system.membus: regStats in group reqLayer14
   47369       0: global: system.membus: regStats in group reqLayer15
   47370       0: global: system.membus: regStats in group reqLayer16
   47371       0: global: system.membus: regStats in group reqLayer2
   47372       0: global: system.membus: regStats in group reqLayer3
   47373       0: global: system.membus: regStats in group reqLayer4
   47374       0: global: system.membus: regStats in group reqLayer5
   47375       0: global: system.membus: regStats in group reqLayer6
   47376       0: global: system.membus: regStats in group reqLayer7
   47377       0: global: system.membus: regStats in group reqLayer8
   47378       0: global: system.membus: regStats in group reqLayer9
   47379       0: global: system.membus: regStats in group respLayer0
   47380       0: global: system.membus: regStats in group respLayer1
   47381       0: global: system.membus: regStats in group respLayer2
   47382       0: global: system.membus: regStats in group respLayer3
   47383       0: global: system.membus: regStats in group respLayer4
   47384       0: global: system.membus: regStats in group respLayer5
      47385       0: global: system.membus: regStats in group respLayer6
   47386       0: global: system.membus: regStats in group respLayer7
   47387       0: global: system.membus: regStats in group snoopLayer0
   47388       0: global: system.membus: regStats in group snoopLayer1
   47389       0: global: system.membus: regStats in group snoopLayer10
   47390       0: global: system.membus: regStats in group snoopLayer11
   47391       0: global: system.membus: regStats in group snoopLayer12
   47392       0: global: system.membus: regStats in group snoopLayer13
   47393       0: global: system.membus: regStats in group snoopLayer14
   47394       0: global: system.membus: regStats in group snoopLayer15
   47395       0: global: system.membus: regStats in group snoopLayer16
   47396       0: global: system.membus: regStats in group snoopLayer2
   47397       0: global: system.membus: regStats in group snoopLayer3
   47398       0: global: system.membus: regStats in group snoopLayer4
   47399       0: global: system.membus: regStats in group snoopLayer5
   47400       0: global: system.membus: regStats in group snoopLayer6
   47401       0: global: system.membus: regStats in group snoopLayer7
   47402       0: global: system.membus: regStats in group snoopLayer8
   47403       0: global: system.membus: regStats in group snoopLayer9
   47404       0: global: system.membus: regStats in group snoop_filter
   47405       0: global: system: regStats in group pci_ide
   47406       0: global: system.pci_ide: regStats in group BAR0
   47407       0: global: system.pci_ide: regStats in group BAR1
   47408       0: global: system.pci_ide: regStats in group BAR2
   47409       0: global: system.pci_ide: regStats in group BAR3
   47410       0: global: system.pci_ide: regStats in group BAR4
   47411       0: global: system.pci_ide: regStats in group BAR5
   47412       0: global: system.pci_ide: regStats in group disks
   47413       0: global: system.pci_ide.disks: regStats in group IdeDisk
   47414       0: global: system.pci_ide.disks: regStats in group image
   47415       0: global: system.pci_ide.disks.image: regStats in group child
   47416       0: global: system.pci_ide: regStats in group power_state
   47417       0: global: system: regStats in group realview
   47418       0: global: system.realview: regStats in group bootmem
   47419       0: global: system.realview.bootmem: regStats in group power_state
   47420       0: global: system.realview: regStats in group clock24MHz
   47421       0: global: system.realview: regStats in group clock32KHz
   47422       0: global: system.realview: regStats in group dcc
   47423       0: global: system.realview.dcc: regStats in group osc_cpu
   47424       0: global: system.realview.dcc: regStats in group osc_ddr
      47425       0: global: system.realview.dcc: regStats in group osc_hsbm
   47426       0: global: system.realview.dcc: regStats in group osc_pxl
   47427       0: global: system.realview.dcc: regStats in group osc_smb
   47428       0: global: system.realview.dcc: regStats in group osc_sys
   47429       0: global: system.realview: regStats in group el2_watchdog
   47430       0: global: system.realview.el2_watchdog: regStats in group power_state
   47431       0: global: system.realview.el2_watchdog: regStats in group ws0
   47432       0: global: system.realview.el2_watchdog: regStats in group ws1
   47433       0: global: system.realview: regStats in group energy_ctrl
   47434       0: global: system.realview.energy_ctrl: regStats in group power_state
   47435       0: global: system.realview: regStats in group flash0
   47436       0: global: system.realview.flash0: regStats in group power_state
   47437       0: global: system.realview: regStats in group flash1
   47438       0: global: system.realview.flash1: regStats in group power_state
   47439       0: global: system.realview: regStats in group generic_timer
   47440       0: global: system.realview.generic_timer: regStats in group int_hyp
   47441       0: global: system.realview.generic_timer: regStats in group int_phys_ns
   47442       0: global: system.realview.generic_timer: regStats in group int_phys_s
   47443       0: global: system.realview.generic_timer: regStats in group int_virt
   47444       0: global: system.realview: regStats in group generic_timer_mem
   47445       0: global: system.realview.generic_timer_mem: regStats in group frames0
   47446       0: global: system.realview.generic_timer_mem.frames0: regStats in group int_phys
   47447       0: global: system.realview.generic_timer_mem.frames0: regStats in group int_virt
   47448       0: global: system.realview.generic_timer_mem.frames0: regStats in group power_state
   47449       0: global: system.realview.generic_timer_mem: regStats in group frames1
   47450       0: global: system.realview.generic_timer_mem.frames1: regStats in group int_phys
   47451       0: global: system.realview.generic_timer_mem.frames1: regStats in group int_virt
   47452       0: global: system.realview.generic_timer_mem.frames1: regStats in group power_state
   47453       0: global: system.realview.generic_timer_mem: regStats in group power_state
   47454       0: global: system.realview: regStats in group gic
   47455       0: global: system.realview.gic: regStats in group power_state
   47456       0: global: system.realview: regStats in group gicv2m
   47457       0: global: system.realview.gicv2m: regStats in group frames
   47458       0: global: system.realview.gicv2m: regStats in group power_state
   47459       0: global: system.realview: regStats in group io_voltage
   47460       0: global: system.realview: regStats in group kmi0
   47461       0: global: system.realview.kmi0: regStats in group interrupt
   47462       0: global: system.realview.kmi0: regStats in group power_state
   47463       0: global: system.realview.kmi0: regStats in group ps2
   47464       0: global: system.realview: regStats in group kmi1
      47465       0: global: system.realview.kmi1: regStats in group interrupt
   47466       0: global: system.realview.kmi1: regStats in group power_state
   47467       0: global: system.realview.kmi1: regStats in group ps2
   47468       0: global: system.realview: regStats in group mcc
   47469       0: global: system.realview.mcc: regStats in group osc_clcd
   47470       0: global: system.realview.mcc: regStats in group osc_mcc
   47471       0: global: system.realview.mcc: regStats in group osc_peripheral
   47472       0: global: system.realview.mcc: regStats in group osc_system_bus
   47473       0: global: system.realview.mcc: regStats in group temp_crtl
   47474       0: global: system.realview: regStats in group non_trusted_sram
   47475       0: global: system.realview.non_trusted_sram: regStats in group power_state
   47476       0: global: system.realview: regStats in group pci_host
   47477       0: global: system.realview.pci_host: regStats in group power_state
   47478       0: global: system.realview: regStats in group pwr_ctrl
   47479       0: global: system.realview.pwr_ctrl: regStats in group power_state
   47480       0: global: system.realview: regStats in group realview_io
   47481       0: global: system.realview.realview_io: regStats in group power_state
   47482       0: global: system.realview: regStats in group rtc
   47483       0: global: system.realview.rtc: regStats in group interrupt
   47484       0: global: system.realview.rtc: regStats in group power_state
   47485       0: global: system.realview: regStats in group sys_counter
   47486       0: global: system.realview: regStats in group system_watchdog
   47487       0: global: system.realview.system_watchdog: regStats in group interrupt
   47488       0: global: system.realview.system_watchdog: regStats in group power_state
   47489       0: global: system.realview: regStats in group trusted_dram
   47490       0: global: system.realview.trusted_dram: regStats in group power_state
   47491       0: global: system.realview: regStats in group trusted_sram
   47492       0: global: system.realview.trusted_sram: regStats in group power_state
   47493       0: global: system.realview: regStats in group trusted_watchdog
   47494       0: global: system.realview.trusted_watchdog: regStats in group interrupt
   47495       0: global: system.realview.trusted_watchdog: regStats in group power_state
   47496       0: global: system.realview: regStats in group uart0
   47497       0: global: system.realview.uart0: regStats in group interrupt
   47498       0: global: system.realview.uart0: regStats in group power_state
   47499       0: global: system.realview: regStats in group uart1
   47500       0: global: system.realview.uart1: regStats in group device
   47501       0: global: system.realview.uart1: regStats in group interrupt
   47502       0: global: system.realview.uart1: regStats in group power_state
   47503       0: global: system.realview: regStats in group uart2
   47504       0: global: system.realview.uart2: regStats in group device
      47505       0: global: system.realview.uart2: regStats in group interrupt
   47506       0: global: system.realview.uart2: regStats in group power_state
   47507       0: global: system.realview: regStats in group uart3
   47508       0: global: system.realview.uart3: regStats in group device
   47509       0: global: system.realview.uart3: regStats in group interrupt
   47510       0: global: system.realview.uart3: regStats in group power_state
   47511       0: global: system.realview: regStats in group vgic
   47512       0: global: system.realview.vgic: regStats in group power_state
   47513       0: global: system.realview: regStats in group vio0
   47514       0: global: system.realview.vio0: regStats in group interrupt
   47515       0: global: system.realview.vio0: regStats in group power_state
   47516       0: global: system.realview.vio0: regStats in group vio
   47517       0: global: system.realview: regStats in group vio1
   47518       0: global: system.realview.vio1: regStats in group interrupt
   47519       0: global: system.realview.vio1: regStats in group power_state
   47520       0: global: system.realview.vio1: regStats in group vio
   47521       0: global: system.realview: regStats in group vram
   47522       0: global: system.realview.vram: regStats in group power_state
   47523       0: global: system.realview: regStats in group watchdog
   47524       0: global: system.realview.watchdog: regStats in group interrupt
   47525       0: global: system.realview.watchdog: regStats in group power_state
   47526       0: global: system: regStats in group release
   47527       0: global: system: regStats in group terminal
   47528       0: global: system: regStats in group vncserver
   47529       0: global: system: regStats in group voltage_domain
   47530       0: global: system: regStats in group workload
   47531       0: global: system.workload: regStats in group inst
   47532 Probes: Call to addPoint "Cycles" to system.cpu.
   47533 Probes: Call to addPoint "ActiveCycles" to system.cpu.
   47534 Probes: Call to addPoint "RetiredInsts" to system.cpu.
   47535 Probes: Call to addPoint "RetiredInstsPC" to system.cpu.
   47536 Probes: Call to addPoint "RetiredLoads" to system.cpu.
   47537 Probes: Call to addPoint "RetiredStores" to system.cpu.
   47538 Probes: Call to addPoint "RetiredBranches" to system.cpu.
   47539 Probes: Call to addPoint "Sleeping" to system.cpu.
   47540 Probes: Call to addPoint "Commit" to system.cpu.
   47541 Probes: Call to addPoint "Hit" to system.cpu.dcache.
   47542 Probes: Call to addPoint "Miss" to system.cpu.dcache.
   47543 Probes: Call to addPoint "Fill" to system.cpu.dcache.
   47544 Probes: Call to addPoint "Data Update" to system.cpu.dcache.
      47545 Probes: Call to addPoint "Hit" to system.cpu.icache.
   47546 Probes: Call to addPoint "Miss" to system.cpu.icache.
   47547 Probes: Call to addPoint "Fill" to system.cpu.icache.
   47548 Probes: Call to addPoint "Data Update" to system.cpu.icache.
   47549 Probes: Call to addPoint "Refills" to system.cpu.mmu.dtb.
   47550 Probes: Call to addPoint "Refills" to system.cpu.mmu.itb.
   47551 Probes: Call to addPoint "Refills" to system.cpu.mmu.l2_shared.
   47552 Probes: Call to addPoint "Refills" to system.cpu.mmu.stage2_dtb.
   47553 Probes: Call to addPoint "Refills" to system.cpu.mmu.stage2_itb.
   47554 Probes: Call to addPoint "Hit" to system.iocache.
   47555 Probes: Call to addPoint "Miss" to system.iocache.
   47556 Probes: Call to addPoint "Fill" to system.iocache.
   47557 Probes: Call to addPoint "Data Update" to system.iocache.
```

接下来是一堆functional的内存写操作从0x8008000开始到0x88002c40，这是物理地址，每次读取64位  大概load了128MB的数据到mem
```
   47558       0: system.membus: recvFunctional: src system.membus.cpu_side_port[0] packet WriteReq [80080000:8008003f]
   47559       0: system.iocache: functionalAccess: WriteReq [80080000:8008003f]
   47560       0: system.cpu.icache: functionalAccess: WriteReq [80080000:8008003f]
   47561       0: system.cpu.dcache: functionalAccess: WriteReq [80080000:8008003f]
   47562       0: system.cpu.dcache_port: recvFunctionalSnoop received functional snoop pkt for addr:0x80080000 WriteReq
   47563       0: global: Write from functional of size 64 on address 0x80080000 C
   47564       0: global: 00000000  10 00 00 14 00 00 00 00  00 00 08 00 00 00 00 00
   47565       0: global: 00000010  00 e0 82 00 00 00 00 00  02 00 00 00 00 00 00 00    `
   47566       0: global: 00000020  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
   47567       0: global: 00000030  00 00 00 00 00 00 00 00  41 52 4d 64 00 00 00 00           ARMd
   47568       0: system.membus: recvFunctional: src system.membus.cpu_side_port[0] packet WriteReq [80080040:8008007f]
   47569       0: system.iocache: functionalAccess: WriteReq [80080040:8008007f]
   47570       0: system.cpu.icache: functionalAccess: WriteReq [80080040:8008007f]
   47571       0: system.cpu.dcache: functionalAccess: WriteReq [80080040:8008007f]
   47572       0: system.cpu.dcache_port: recvFunctionalSnoop received functional snoop pkt for addr:0x80080040 WriteReq
   47573       0: global: Write from functional of size 64 on address 0x80080040 C
   47574       0: global: 00000000  09 00 00 94 af 05 00 94  18 fc ff 90 e5 05 00 94       /    |  e
   47575       0: global: 00000010  0d 00 00 94 7b 0b 00 58  9e 2a 00 90 de 03 00 91       {  X *  ^
   47576       0: global: 00000020  98 53 15 14 f5 03 00 aa  40 3b 00 d0 00 00 02 91    S  u  *@; P
   47577       0: global: 00000030  15 04 00 a9 02 0c 01 a9  bf 3f 03 d5 01 80 00 91      )   )?? U
   47578       0: system.membus: recvFunctional: src system.membus.cpu_side_port[0] packet WriteReq [80080080:800800bf]
   47579       0: system.iocache: functionalAccess: WriteReq [80080080:800800bf]
   47580       0: system.cpu.icache: functionalAccess: WriteReq [80080080:800800bf]
   47581       0: system.cpu.dcache: functionalAccess: WriteReq [80080080:800800bf]
   ...
    1386268       0: system.membus: recvFunctional: src system.membus.cpu_side_port[0] packet WriteReq [88002c40:88002c55]
 1386269       0: system.iocache: functionalAccess: WriteReq [88002c40:88002c55]
 1386270       0: system.cpu.icache: functionalAccess: WriteReq [88002c40:88002c55]
 1386271       0: system.cpu.dcache: functionalAccess: WriteReq [88002c40:88002c55]
 1386272       0: system.cpu.dcache_port: recvFunctionalSnoop received functional snoop pkt for addr:0x88002c40 WriteReq
 1386273       0: global: Write from functional of size 22 on address 0x88002c40 C
 1386274       0: global: 00000000  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00
 1386275       0: global: 00000010  00 00 00 00 00 00
```

随后是
```
 1386276       0: system.cpu.[tid:0]: Setting int reg 0 (0) to 0x88000000.
 1386277       0: system.cpu.[tid:0]: Setting int reg 5 (5) to 0x87fffff8.
 1386278       0: system.clk_domain: Setting clock period to 1000 ticks for source clock system.clk_domain
 1386279       0: system.cpu_clk_domain: Setting clock period to 500 ticks for source clock system.cpu_clk_domain
 1386280       0: system.realview.clock24MHz: Setting clock period to 41667 ticks for source clock system.realview.clock24MHz
 1386281       0: system.realview.clock32KHz: Setting clock period to 31250000 ticks for source clock system.realview.clock32KH         z
 1386282       0: global: PC based event scheduled for 0xffffffc000134600: Kernel panic in simulated kernel
 1386283       0: global: PC based event scheduled for 0xffffffc0000ac248: Kernel oops in guest
 1386284       0: global: PC based event scheduled for 0xffffffc0002bc4d8: __udelay
 1386285       0: global: PC based event scheduled for 0xffffffc0002bc4a0: __const_udelay
```
来到了真正的日志
```
 1386286 gem5 Simulator System.  http://gem5.org
 1386287 gem5 is copyrighted software; use the --copyright option for details.
 1386288 
 1386289 gem5 version 21.2.0.0
 1386290 gem5 compiled Mar  3 2023 15:19:37
 1386291 gem5 started Apr  7 2023 16:17:56
 1386292 gem5 executing on fee605e4571d, pid 29535
 1386293 command line: build/ARM/gem5.opt --outdir=/home/test_o3_l3_classic/ --debug-flags=All configs/example/fs.py --cpu-type         =AtomicSimpleCPU --mem-size=8GB -n1 --bootloader=/home/binaries/boot.arm64 --disk-image=ubuntu-18.04-arm64-docker-add-         spec.img --kernel=vmlinux-4.14 --caches
```
从地址0x000010开始ifetch 执行流为0x000010->0xPC:0x000104
**这段代码为bootloader的代码！**
所以80080000的代码是内核代码！
随后执行刚才load的128M
PC:0x80080000->。。。
```
 1386296       0: Event_984: generic 984 scheduled @ 0
 1386297       0: Event_984: generic 984 rescheduled @ 18446744073709551615
 1386298       0: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 executed @ 0
 1386299       0: system.cpu: Tick
 1386300       0: system.cpu: Fetch: Inst PC:0x000010, Fetch PC:0x000010
 1386301       0: system.cpu.mmu: TLB variables changed!
 1386302       0: system.cpu.isa: Reading MiscReg sctlr_el1 with clear res1 bits: 0x8000000
 1386303       0: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1386304       0: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1386305       0: system.cpu.mmu: translateFs addr 0x10, mode 2, st2 0, scr 0 sctlr 0x30d50830 flags 0x100 tranType 0x0
 1386306       0: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1386307       0: system.cpu.mmu: (No MMU) setting memory attributes: shareable: 1, innerAttrs: 0, outerAttrs: 0, stage2: 0
 1386308       0: system.cpu.icache: access for ReadReq [10:13] IF UC
 1386309       0: system.cpu.icache: handleAtomicReqMiss: Sending an atomic ReadReq [10:13] IF UC
 1386310       0: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [10:13] IF UC
 1386311       0: system.membus.snoop_filter: lookupRequest: src system.membus.cpu_side_port[2] packet ReadReq [10:13] IF UC
 1386312       0: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [10:13] IF UC SF size: 0          lat: 1
 1386313       0: global: IFetch from cpu.inst of size 4 on address 0x10 data 0xaa0003f5 U
 1386314       0: system.membus.snoop_filter: updateResponse: src system.membus.cpu_side_port[2] packet ReadResp [10:13] IF UC
 1386315       0: system.cpu.icache: handleAtomicReqMiss: Receive response: ReadResp [10:13] IF UC for
 1386316       0: system.cpu.[tid:0]: Setting int reg 34 (34) to 0.
 1386317       0: system.cpu.decoder: Arm inst: 0x4aa0003f5.
 1386318       0: system.cpu.decoder: Decode: Decoded orr instruction: 0x4aa0003f5
 1386319       0: system.cpu.[tid:0]: Reading int reg 0 (0) as 0x88000000.
 1386320       0: system.cpu.[tid:0]: Reading int reg 31 (34) as 0.
 1386321       0: system.cpu.[tid:0]: Setting int reg 21 (21) to 0x88000000.
 1386322       0: system.cpu: A0 T0 : 0x10 @__reg_num_x16    :   orr   x21, xzr, x0       : IntAlu :  D=0x0000000088000000  fla         gs=(IsInteger)
 1386323       0: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 rescheduled @ 500
 1386324     500: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 executed @ 500
 1386325     500: system.cpu: Tick
 1386326     500: system.cpu: Fetch: Inst PC:0x000014, Fetch PC:0x000014
 1386327     500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1386328     500: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1386329     500: system.cpu.mmu: translateFs addr 0x14, mode 2, st2 0, scr 0 sctlr 0x30d50830 flags 0x100 tranType 0x0
 1386330     500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1386331     500: system.cpu.mmu: (No MMU) setting memory attributes: shareable: 1, innerAttrs: 0, outerAttrs: 0, stage2: 0
 1386332     500: system.cpu.icache: access for ReadReq [14:17] IF UC
```
从0x80080000开始,第一条指令就b到了kernel_init代码
```
 1387074   13500: system.cpu: A0 T0 : 0x80080000 @kernel_init._text    :   b   <kernel_init.stext>  : IntAlu :   flags=(IsC         ontrol|IsDirectControl|IsUncondControl)
```


```
1387054   13500: system.cpu: Tick
 1387055   13500: system.cpu: Fetch: Inst PC:0x80080000, Fetch PC:0x80080000
 1387056   13500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387057   13500: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1387058   13500: system.cpu.mmu: translateFs addr 0x80080000, mode 2, st2 0, scr 0 sctlr 0x30d50830 flags 0x100 tranType 0         x0
 1387059   13500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387060   13500: system.cpu.mmu: (No MMU) setting memory attributes: shareable: 1, innerAttrs: 0, outerAttrs: 0, stage2: 0
 1387061   13500: system.cpu.icache: access for ReadReq [80080000:80080003] IF UC
 1387062   13500: system.cpu.icache: handleAtomicReqMiss: Sending an atomic ReadReq [80080000:80080003] IF UC
 1387063   13500: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [80080000:80080003]          IF UC
 1387064   13500: system.membus.snoop_filter: lookupRequest: src system.membus.cpu_side_port[2] packet ReadReq [80080000:80         080003] IF UC
 1387065   13500: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [80080000:80080003]          IF UC SF size: 0 lat: 1
 1387066   13500: system.mem_ctrls: recvAtomic: ReadReq 0x80080000
 1387067   13500: global: IFetch from cpu.inst of size 4 on address 0x80080000 data 0x14000010 U
 1387068   13500: system.membus.snoop_filter: updateResponse: src system.membus.cpu_side_port[2] packet ReadResp [80080000:         80080003] IF UC
 1387069   13500: system.cpu.icache: handleAtomicReqMiss: Receive response: ReadResp [80080000:80080003] IF UC for
 1387070   13500: system.cpu.[tid:0]: Setting int reg 34 (34) to 0.
 1387071   13500: system.cpu.decoder: Arm inst: 0x414000010.
 1387072   13500: system.cpu.decoder: Decode: Decoded b instruction: 0x414000010
 1387073   13500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387074   13500: system.cpu: A0 T0 : 0x80080000 @kernel_init._text    :   b   <kernel_init.stext>  : IntAlu :   flags=(IsC         ontrol|IsDirectControl|IsUncondControl)
 1387075   13500: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 rescheduled @ 14000
 1387076   14000: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 executed @ 14000
 1387077   14000: system.cpu: Tick
 1387078   14000: system.cpu: Fetch: Inst PC:0x80080040, Fetch PC:0x80080040
 1387079   14000: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387080   14000: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1387081   14000: system.cpu.mmu: translateFs addr 0x80080040, mode 2, st2 0, scr 0 sctlr 0x30d50830 flags 0x100 tranType 0         x0
 1387082   14000: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387083   14000: system.cpu.mmu: (No MMU) setting memory attributes: shareable: 1, innerAttrs: 0, outerAttrs: 0, stage2: 0
 1387084   14000: system.cpu.icache: access for ReadReq [80080040:80080043] IF UC
 1387085   14000: system.cpu.icache: handleAtomicReqMiss: Sending an atomic ReadReq [80080040:80080043] IF UC
 1387086   14000: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [80080040:80080043]          IF UC
 1387087   14000: system.membus.snoop_filter: lookupRequest: src system.membus.cpu_side_port[2] packet ReadReq [80080040:80         080043] IF UC
 1387088   14000: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [80080040:80080043]          IF UC SF size: 0 lat: 1
 1387089   14000: system.mem_ctrls: recvAtomic: ReadReq 0x80080040
 1387090   14000: global: IFetch from cpu.inst of size 4 on address 0x80080040 data 0x94000009 U
 1387091   14000: system.membus.snoop_filter: updateResponse: src system.membus.cpu_side_port[2] packet ReadResp [80080040:         80080043] IF UC
 1387092   14000: system.cpu.icache: handleAtomicReqMiss: Receive response: ReadResp [80080040:80080043] IF UC for
 1387093   14000: system.cpu.[tid:0]: Setting int reg 34 (34) to 0.
 1387094   14000: system.cpu.decoder: Arm inst: 0x494000009.
 1387095   14000: system.cpu.decoder: Decode: Decoded bl instruction: 0x494000009
 1387096   14000: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387097   14000: system.cpu.[tid:0]: Setting int reg 30 (33) to 0x80080044.
 1387098   14000: system.cpu: A0 T0 : 0x80080040 @kernel_init.stext    :   bl   <kernel_init.preserve_boot_args> : IntAlu :           D=0x0000000080080044  flags=(IsInteger|IsControl|IsDirectControl|IsUncondControl|IsCall)
 1387099   14000: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 rescheduled @ 14500
 1387100   14500: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 executed @ 14500
 1387101   14500: system.cpu: Tick
 1387102   14500: system.cpu: Fetch: Inst PC:0x80080064, Fetch PC:0x80080064
 1387103   14500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387104   14500: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1387105   14500: system.cpu.mmu: translateFs addr 0x80080064, mode 2, st2 0, scr 0 sctlr 0x30d50830 flags 0x100 tranType 0         x0
 1387106   14500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1387107   14500: system.cpu.mmu: (No MMU) setting memory attributes: shareable: 1, innerAttrs: 0, outerAttrs: 0, stage2: 0
 1387108   14500: system.cpu.icache: access for ReadReq [80080064:80080067] IF UC
 1387109   14500: system.cpu.icache: handleAtomicReqMiss: Sending an atomic ReadReq [80080064:80080067] IF UC
 1387110   14500: system.membus: recvAtomicBackdoor: src system.membus.cpu_side_port[2] packet ReadReq [80080064:80080067]          IF UC
```

快进到后边的代码 mmu已经开始使用了，操作系统已经把mmu模块初始化成功了？
```
 1899970 10902500: system.cpu.mmu: Translating VA=0xffffffc0000801f4 context=0
```
```
1899965 10902500: system.cpu: Tick
 1899966 10902500: system.cpu: Fetch: Inst PC:0xffffffc0000801f4, Fetch PC:0xffffffc0000801f4
 1899967 10902500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1899968 10902500: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
 1899969 10902500: system.cpu.mmu: translateFs addr 0xffffffc0000801f4, mode 2, st2 0, scr 0 sctlr 0x34d5d91d flags 0x100 t         ranType 0x0
 1899970 10902500: system.cpu.mmu: Translating VA=0xffffffc0000801f4 context=0
 1899971 10902500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1899972 10902500: system.cpu.mmu.itb: Lookup 0xffffffc0000801f4, asn 0 -> hit vmn 0x0 hyp 0 secure 0 ppn 0x400 size: 0x1ff         fff pa: 0x800801f4 ap:0 ns:1 nstid:1 g:1 asid: 0 el: 1
 1899973 10902500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1899974 10902500: system.cpu.mmu: Checking S1 permissions: ap:0, xn:0, pxn:0, r:0, w:0, x:1, is_priv: 1, wxn: 0
 1899975 10902500: system.cpu.mmu: Setting memory attributes: shareable: 0, innerAttrs: 0, outerAttrs: 0, mtype: 2, stage2:          0
 1899976 10902500: system.cpu.icache: access for ReadReq [800801f4:800801f7] IF hit state: 6 (E) writable: 1 readable: 1 di         rty: 0 prefetched: 0 | tag: 0x20020 secure: 0 valid: 1 | set: 0x7 way: 0
 1899977 10902500: system.cpu.[tid:0]: Setting int reg 34 (34) to 0.
 1899978 10902500: system.cpu.decoder: Arm inst: 0x417fffffd.
 1899979 10902500: system.cpu.decoder: Decode: Decoded b instruction: 0x417fffffd
 1899980 10902500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
 1899981 10902500: system.cpu: A0 T0 : 0xffffffc0000801f4 @__mmap_switched+28    :   b   <__mmap_switched+16> : IntAlu :            flags=(IsControl|IsDirectControl|IsUncondControl)
 1899982 10902500: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 rescheduled @ 10903000
 1899983 10903000: AtomicSimpleCPU tick.wrapped_function_event: EventFunctionWrapped 77 executed @ 10903000
```

一直到这次测试启动得最后的阶段还在执行这部分128M代码
```
10792240 207776500: system.cpu: Tick
10792241 207776500: system.cpu: Fetch: Inst PC:0xffffffc0002bcd34, Fetch PC:0xffffffc0002bcd34
10792242 207776500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
10792243 207776500: system.cpu.mmu: CPSR is priv:1 UserMode:0 secure:0 S1S2NsTran:0
10792244 207776500: system.cpu.mmu: translateFs addr 0xffffffc0002bcd34, mode 2, st2 0, scr 0 sctlr 0x34d5d91d flags 0x100          tranType 0x0
10792245 207776500: system.cpu.mmu: Translating VA=0xffffffc0002bcd34 context=0
10792246 207776500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
10792247 207776500: system.cpu.mmu.itb: Lookup 0xffffffc0002bcd34, asn 0 -> hit vmn 0x0 hyp 0 secure 0 ppn 0x401 size: 0x1f         ffff pa: 0x802bcd34 ap:0 ns:1 nstid:1 g:1 asid: 0 el: 1
10792248 207776500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
10792249 207776500: system.cpu.mmu: Checking S1 permissions: ap:0, xn:0, pxn:0, r:0, w:0, x:1, is_priv: 1, wxn: 0
10792250 207776500: system.cpu.mmu: Setting memory attributes: shareable: 0, innerAttrs: 0, outerAttrs: 0, mtype: 2, stage2         : 0
10792251 207776500: system.cpu.icache: access for ReadReq [802bcd34:802bcd37] IF hit state: 6 (E) writable: 1 readable: 1 d         irty: 0 prefetched: 0 | tag: 0x200af secure: 0 valid: 1 | set: 0x34 way: 0
10792252 207776500: system.cpu.[tid:0]: Setting int reg 34 (34) to 0.
10792253 207776500: system.cpu.decoder: Arm inst: 0x4d65f03c0.
10792254 207776500: system.cpu.decoder: Decode: Decoded ret instruction: 0x4d65f03c0
10792255 207776500: system.cpu.[tid:0]: Reading int reg 30 (33) as 0xffffffc0007930fc.
10792256 207776500: system.cpu.isa: Reading MiscReg scr with clear res1 bits: 0x30
10792257 207776500: system.cpu: A0 T0 : 0xffffffc0002bcd34 @strcmp+180    :   ret                      : IntAlu :   flags=(         IsInteger|IsControl|IsIndirectControl|IsUncondControl|IsReturn)
```
按照之前的统计： 
gem5 fs启动 + shell + libquantem 总指令数为：542223246
gem5 se启动 libquantem总指令数为 202033082
所以推算系统启动代码量为300000000

那么linux操作系统初始化做了些什么？
https://blog.csdn.net/viewsky11/article/details/53040564
在系统启动过程中，主要关注一下几个方面：
中断系统及调度系统
文件系统的初始化
设备管理系统的初始化
网络协议的初始化

device tree blob(DTB)由bootloader传入内核