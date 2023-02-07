# C++子类获取父类大小

遇到的实际问题是，想获取一个基类所有继承类的大小范围，但所有继承类的数量太多，继承类都散落在代码中，使用sizeof方法不好枚举所有继承类。

一个替代方案
- 重写基类的new方法，打印出继承类的实际大小，收集大小信息
- 执行一个可以遍历到所有继承类的new函数的程序

重写基类new方法实例
```
class StaticInst 
{
    ... 
    
    void* operator new(std::size_t size) {
        std::cout << "operator new, size: " << std::dec << size << std::endl;
        return std::malloc(size);
    }
}
```