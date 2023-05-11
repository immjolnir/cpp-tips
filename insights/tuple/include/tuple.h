
#include <cmath>
#include <type_traits>  // std::enable_if_t for c++11
#include <utility>      // std::tuple_element

#include "impl/impl.h"

namespace dts {
    // See  /usr/include/c++/11/tuple
    template <typename... _Elements>
    class Tuple;

    /**
     * Contains the actual implementation of the @c tuple template, stored
     * as a recursive inheritance hierarchy from the first element (most
     * derived class) to the last (least derived class). The @c Idx
     * parameter gives the 0-based index of the element stored at this
     * point in the hierarchy; we use it to implement a constant-time
     * get() operation.
     */
    template <size_t _Idx, typename... _Elements>
    struct _Tuple_impl;

    /// Primary class template, tuple
    template <typename... _Elements>
    class Tuple : public _Tuple_impl<0, _Elements...> {
      public:
        /// Return a reference to the ith element of a tuple.
        template <size_t __i, typename... _Elements>
        constexpr std::tuple_element_t<__i, tuple<_Elements...>>& get(tuple<_Elements...>& __t) noexcept {
            return std::__get_helper<__i>(__t);
        }

        /// Return a reference to the unique element of type _Tp of a tuple.
        template <typename _Tp, typename... _Types>
        constexpr _Tp& get(tuple<_Types...>& __t) noexcept {
            constexpr size_t __idx = __find_uniq_type_in_pack<_Tp, _Types...>();
            static_assert(__idx < sizeof...(_Types), "the type T in std::get<T> must occur exactly once in the tuple");
            return std::__get_helper<__idx>(__t);
        }

      private:
        // Return the index of _Tp in _Types, if it occurs exactly once.
        // Otherwise, return sizeof...(_Types).
        // TODO reuse this for __detail::__variant::__exactly_once.
        template <typename _Tp, typename... _Types>
        constexpr size_t __find_uniq_type_in_pack() {
            constexpr size_t __sz = sizeof...(_Types);
            constexpr bool __found[__sz] = {__is_same(_Tp, _Types)...};
            size_t __n = __sz;
            for (size_t __i = 0; __i < __sz; ++__i) {
                if (__found[__i]) {
                    if (__n < __sz)  // more than one _Tp found
                        return __sz;
                    __n = __i;
                }
            }
            return __n;
        }

        template <size_t __i, typename _Head, typename... _Tail>
        constexpr _Head& __get_helper(_Tuple_impl<__i, _Head, _Tail...>& __t) noexcept {
            return _Tuple_impl<__i, _Head, _Tail...>::_M_head(__t);
        }

        // Deleted overload to improve diagnostics for invalid indices
        template <size_t __i, typename... _Types>
        std::enable_if_t<(__i >= sizeof...(_Types))> __get_helper(const tuple<_Types...>&) = delete;
    };

}  // namespace dts
