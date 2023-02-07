# 分离出一个好用的decoder

### 作为毕业论文是否足够？
- 创新点有什么？已经存在了多种架构的decoder的情况下，decoder的创新点在哪里？
  - 平坦的信息类型，利于指令分析，数量统计，利于指令集分析工具使用（dynamorio的opcode分析）
  - ？
- 是否要支持类似decoder的主打功能：反汇编？
  - gem5支持反汇编的时候，需要所有的指令信息类相关的东西，就不轻量级了
相关的工作有什么

### 相关工作：
[参考自](https://hvmi.github.io/blog/2020/11/04/bddisasm.html)

- [Intel Xed](https://intelxed.github.io/), 由 Intel 编写和维护，因此以某种方式使其成为标准的 x86 解码器；虽然不是最快的，但它提供了有关解码指令的丰富信息；
- [ZyDis](https://github.com/zyantific/zydis), 与 Xed 相当，而且轻量级
- [Capstone](https://github.com/capstone-engine/capstone/tree/next), 多种架构的解码器的集合



