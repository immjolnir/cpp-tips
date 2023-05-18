# [How does auto deduce type?](https://stackoverflow.com/questions/21070032/how-does-auto-deduce-type)

The type deduced for auto in the declaration of a variable is defined via the rules of template argument deduction, see [dcl.spec.auto]/6; with one exception: if the initializer is a braced-init-list, the deduced type is a std::initializer_list.


* https://subscription.packtpub.com/book/programming/9781786465184/1/ch01lvl1sec5/using-auto-whenever-possible
> As mentioned earlier, auto does not retain const/volatile and reference qualifiers. 

* https://iamsorush.com/posts/auto-cpp/


## [When auto Seemingly Deduces a Reference in C++](https://blog.petrzemek.net/2017/12/08/when-auto-seemingly-deduces-a-reference-in-cpp/)
* exam01.cpp
* exam02.cpp
* exam03.cpp
* exam04.cpp

* exam05.cpp

# std::vector<bool>



* /usr/include/c++/11/bits/stl_bvector.h:906
```
  /**
   *  @brief  A specialization of vector for booleans which offers fixed time
   *  access to individual elements in any order.
   *
   *  @ingroup sequences
   *
   *  @tparam _Alloc  Allocator type.
   *
   *  Note that vector<bool> does not actually meet the requirements for being
   *  a container.  This is because the reference and pointer types are not
   *  really references and pointers to bool.  See DR96 for details.  @see
   *  vector for function documentation.
   *
   *  In some terminology a %vector can be described as a dynamic
   *  C-style array, it offers fast and efficient access to individual
   *  elements in any order and saves the user from worrying about
   *  memory and size allocation.  Subscripting ( @c [] ) access is
   *  also provided as with C-style arrays.
  */
  template<typename _Alloc>
    class vector<bool, _Alloc> : protected _Bvector_base<_Alloc>
    {
        typedef _Bit_reference                reference;
        typedef bool                  const_reference;
...
905	      reference
906	      operator[](size_type __n)
907	      { return begin()[__n]; }
909	      const_reference
910	      operator[](size_type __n) const
911	      { return begin()[__n]; }
```
And the `_Bit_reference` is 
```
  struct _Bit_reference
  {
    _Bit_type * _M_p;
    _Bit_type _M_mask;

    _Bit_reference(_Bit_type * __x, _Bit_type __y)
    : _M_p(__x), _M_mask(__y) { }

    _Bit_reference() _GLIBCXX_NOEXCEPT : _M_p(0), _M_mask(0) { }

#if __cplusplus >= 201103L
    _Bit_reference(const _Bit_reference&) = default;
#endif

    operator bool() const _GLIBCXX_NOEXCEPT
    { return !!(*_M_p & _M_mask); }

    _Bit_reference&
    operator=(bool __x) _GLIBCXX_NOEXCEPT
    {
      if (__x)
    *_M_p |= _M_mask;
      else
    *_M_p &= ~_M_mask;
      return *this;
    }

    _Bit_reference&
    operator=(const _Bit_reference& __x) _GLIBCXX_NOEXCEPT
    { return *this = bool(__x); }

    bool
    operator==(const _Bit_reference& __x) const
    { return bool(*this) == bool(__x); }

    bool
    operator<(const _Bit_reference& __x) const
    { return !bool(*this) && bool(__x); }

    void
    flip() _GLIBCXX_NOEXCEPT
    { *_M_p ^= _M_mask; }
  };

```
But how it works?

