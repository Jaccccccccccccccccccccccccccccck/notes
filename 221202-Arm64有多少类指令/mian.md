#Arm64指令种类数

## 来源
取自
- [arm64 base指令列表](https://developer.arm.com/documentation/ddi0602/2022-09/Base-Instructions?lang=en)
- [arm64 SIMD&FP指令列表](https://developer.arm.com/documentation/ddi0596/2021-09/SIMD-FP-Instructions)
- [arm64 SVE指令列表](https://developer.arm.com/documentation/ddi0596/2021-09/SVE-Instructions)

## 以opcode为类别统计数量
- [计算脚本](./arm64_inst_type_parser.py) 
- 指令文件
  - [文字版base指令列表](./arm64_inst_types.txt)
  - [文字版SIMD&FP指令列表](./arm64_SIMD_FP_insts.txt)
  - [文字版SVE指令列表](./arm64_sve_insts.txt)
### 为何要额外处理
- 合并同一个opcode因operands不同导致的多类别，如下例
  - ADD (extended register): Add (extended register).
  - ADD (immediate): Add (immediate).
- 展开一类别中的所有的opcode，如下例
  - CAS, CASA, CASAL, CASL

## 数量
1503
```
./arm64_base_insts.txt types: 689
./arm64_SIMD_FP_insts.txt types: 348
./arm64_sve_insts.txt types: 323
```

## x86有多少指令？
- 1503 [一篇博客结论](https://fgiesen.wordpress.com/2016/08/25/how-many-x86-instructions-are-there/)
- 1636 [一篇论文的结论](https://www.unomaha.edu/college-of-information-science-and-technology/research-labs/_files/enumerating-x86-64-instructions.pdf)
