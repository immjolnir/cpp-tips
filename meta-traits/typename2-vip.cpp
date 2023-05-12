
/*
 See https://sg-first.gitbooks.io/cpp-template-tutorial/content/jie_te_hua_yu_pian_te_hua.html

$ clang++ -Xclang -ast-print -fsyntax-only typename2.cpp

*/
template <typename T>
struct DoWork {};  // 这是原型

template <>
struct DoWork<int> {};  // 这是 int 类型的"重载"

template <>
struct DoWork<float> {};  // 这是 float 类型的"重载"

template <>
struct DoWork<int, int> {};  // 这是 int, int 类型的“重载”

void f() {
    DoWork<int> i;
    DoWork<float> f;
    DoWork<int, int> ii;
}
