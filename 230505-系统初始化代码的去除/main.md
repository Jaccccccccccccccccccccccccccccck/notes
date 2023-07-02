# gem5系统初始化代码
#### Gem5系统初始化包括从Bootloader到返回操作界面bash的过程

虽然gem5的教程视频[here](https://www.youtube.com/watch?v=dMVrNyYqfMA)中称没有bootloader过程，但确实项目中确实存在bootloader的文件，也被流水线执行了

#### 系统初始化代码分为三个部分
Bootloader → Linux init → shell

要找到相应代码?

#### FS Gem5配置文件入口
configs/example/fs.py
```
test_sys.workload.object_file = binary(args.kernel)

Simulation.setWorkCountOptions(test_sys, args)
Simulation.run(args, root, test_sys, FutureClass)
```
root为模拟对象的主对象，由test_sys初始化而来
#### 查看simulation代码
configs/common/Simulation.py 中定义run
前边很长一段在为m5设置传进来的参数,最终调用了m5.instantiate(checkpoint_dir) 并进入 benchCheckpoints()函数，输出日志说明benchCheckpoints函数为真正的simulation
```
def run(options, root, testsys, cpu_class):
    ...
    m5.instantiate(checkpoint_dir)
    ...
    exit_event = benchCheckpoints(options, maxtick, cptdir)
    ...
    print('Exiting @ tick %i because %s' %
          (m5.curTick(), exit_event.getCause()))
    ...
```
benchCheckpoints函数内部调用了m5.simulate函数
```
def benchCheckpoints(options, maxtick, cptdir):
    exit_event = m5.simulate(maxtick - m5.curTick())
    exit_cause = exit_event.getCause()

    num_checkpoints = 0
    max_checkpoints = options.max_checkpoints

    while exit_cause == "checkpoint":
        m5.checkpoint(joinpath(cptdir, "cpt.%d"))
        num_checkpoints += 1
        if num_checkpoints == max_checkpoints:
            exit_cause = "maximum %d checkpoints dropped" % max_checkpoints
            break

        exit_event = m5.simulate(maxtick - m5.curTick())
        exit_cause = exit_event.getCause()

    return exit_event
```

src/sim/simulate.cc 中在函数doSimLoop中eventq->serviceOne()打上断点，可以看到已经开始执行bootloader的代码了，但是从哪里分配的第一个事件？

所有的event调度的时候都有schedule函数？找到第一个schedule函数

#### 调用路径

初始化，第一个schedule函数，schedule一个thread0的cpu tick函数
```
gem5::ArmISA::FsLinux::initState()
    ->gem5::ArmISA::FsWorkload::initState()
        ->gem5::o3::ThreadContext::activate()
            ->gem5::o3::CPU::activateContext()
                ->gem5::o3::CPU::scheduleTickEvent()
```

### gem5 fs模式下的thread是host的thread

#### Fs启动日志
```

...
build/ARM/arch/arm/fs_workload.cc:121: info: Using bootloader at address 0x10
build/ARM/arch/arm/fs_workload.cc:139: info: Using kernel entry physical address at 0x80080000
build/ARM/arch/arm/linux/fs_workload.cc:97: info: Loading DTB file: /home/testO3/system.dtb at address 0x88000000
**** REAL SIMULATION ****
...

```

这里对应了系统初始化的一些步骤，加载bootloader的代码，加载kenel的代码，加载DTB文件
build/ARM/arch/arm/fs_workload.cc
```
void
FsWorkload::initState()
{
    KernelWorkload::initState();

    // 将bootloader写入物理内存
    bootldr->buildImage().write(system->physProxy);

    for (auto *tc: arm_sys->threads) {
        tc->setIntReg(3, kernelEntry);
        if (is_gic_v2)
            tc->setIntReg(4, arm_sys->params().gic_cpu_addr);
        if (getArch() == loader::Arm)
            tc->setIntReg(5, params().cpu_release_addr);
    }
    // kernel的写入代码在哪里？
    inform("Using kernel entry physical address at %#x\n", kernelEntry);
}
```






