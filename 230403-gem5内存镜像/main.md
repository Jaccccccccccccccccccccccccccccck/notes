### MemoryImage的结构
MemoryImage中存在一个Segment列表，**添加**和**取**segment的函数
Segment中存储了段名称、首地址、真实数据、大小信息
```
class MemoryImage
{
  public:
    struct Segment
    {
        ImageFileDataPtr ifd;
        std::string name;  // 段名称
        Addr base = 0;  // 首地址
        const uint8_t *data = nullptr;  // 数据
        size_t size = 0;  // 大小
    };

  private:
    std::vector<Segment> _segments;
    bool writeSegment(const Segment &seg, const PortProxy &proxy) const;
};

```

### MemoryImage如何使用
在abstract_mem.cc文件中，在这里传入的file参数是空的，直接return了
```
void
AbstractMemory::initState()
{
    ClockedObject::initState();

    const auto &file = params().image_file;
    if (file == "")
        return;

    auto *object = loader::createObjectFile(file, true);
    fatal_if(!object, "%s: Could not load %s.", name(), file);

    loader::debugSymbolTable.insert(*object->symtab().globals());
    loader::MemoryImage image = object->buildImage();

    AddrRange image_range(image.minAddr(), image.maxAddr());
    if (!range.contains(image_range.start())) {
        warn("%s: Moving image from %s to memory address range %s.",
                name(), image_range.to_string(), range.to_string());
        image = image.offset(range.start());
        image_range = AddrRange(image.minAddr(), image.maxAddr());
    }
    panic_if(!image_range.isSubset(range), "%s: memory image %s doesn't fit.",
             name(), file);

    PortProxy proxy([this](PacketPtr pkt) { functionalAccess(pkt); },
                    system()->cacheLineSize());

    panic_if(!image.write(proxy), "%s: Unable to write image.");
}
```

在 src/sim/process.cc文件中
```
Process::Process()
{
    fatal_if(!seWorkload, "Couldn't find appropriate workload object.");
    fatal_if(_pid >= System::maxPID, "_pid is too large: %d", _pid);

    exitGroup = new bool();
    sigchld = new bool();

    image = objFile->buildImage();

    if (loader::debugSymbolTable.empty())
        loader::debugSymbolTable = objFile->symtab();
}
```