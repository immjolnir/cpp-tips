// See  /usr/include/c++/11/tuple

namespace dts {
    /**
     * Recursive tuple implementation. Here we store the @c Head element
     * and derive from a @c Tuple_impl containing the remaining elements
     * (which contains the @c Tail).
     */
    template <size_t _Idx, typename _Head, typename... _Tail>
    struct _Tuple_impl<_Idx, _Head, _Tail...> : public _Tuple_impl<_Idx + 1, _Tail...>,
                                                private _Head_base<_Idx, _Head> {};

}  // namespace dts
