// See /home/zhishan/iwork/cpp-tips/3rdparty/MetaNN/readme_eng.md
//
The most basic type of data represented in MetaNN is Tensor. For example, you can declare a Tensor in the following way:
```cpp
Tensor<int, DeviceTags::CPU, 2> matrix(10, 20);
```
This is equivalent to defining a matrix with 10 rows and 20 columns in each row. The data element type of the object is ```int```, and the computing device supported is ```CPU```.

The system introduces several aliases for ```Tensor```, such as:
```cpp
template <typename TElem, typename TDevice>
using Matrix = Tensor<TElem, TDevice, 2>;
```
Therefore, the following definition is equivalent to the above definition:
```cpp
Matrix<int, DeviceTags::CPU> matrix(10, 20);
```
