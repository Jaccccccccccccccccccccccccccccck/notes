# Pybind用来做什么？

#### 简单来说，pybind提供了python调用c++方法的易用接口，可以用来提升python的性能，在gem5中用python给c++提供方便的配置接口
- 使用c++调用python也提供了方法，但好像没啥用？


#### 一个简单的例子 [form here](https://pybind11.readthedocs.io/en/stable/basics.html)
**example.cpp**: c++文件中定义需要使用的模块(此例子中是example模块)和函数（add函数）

```
#include <pybind11/pybind11.h>

namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(example, m) {
    m.doc() = "pybind11 example plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");
}
```

把这个c++文件编译成库，生成文件**example.cpython-36m-x86_64-linux-gnu.so**
```
$ c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) example.cpp -o example$(python3-config --extension-suffix)
```

在当前路径下执行python，即可import example模块并使用add方法
```
$ python
Python 3.9.10 (main, Jan 15 2022, 11:48:04)
[Clang 13.0.0 (clang-1300.0.29.3)] on darwin
Type "help", "copyright", "credits" or "license" for more information.
>>> import example
>>> example.add(1, 2)
3
>>>
```
