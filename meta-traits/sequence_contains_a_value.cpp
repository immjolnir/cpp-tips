#include <cxxabi.h>

#include <type_traits>
#include <utility>  // index_sequence

#include <array>
#include <cmath>
#include <iostream>

template <typename T>
void echo() {
    int status;
    char* realname;
    const std::type_info& ti = typeid(T);
    realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
    std::cout << "Type Signature: \n\t" << ti.name() << "\n\t=> " << realname << "\n\t: " << status << '\n'
              << std::endl;
}

namespace MetaNN {
    template <size_t... uDims>
    struct PDimArrayIs {
        static constexpr std::array<size_t, sizeof...(uDims)> DimArray{uDims...};
    };

    template <bool... uDims>
    struct PDimBitArrayIs {
        static constexpr std::array<bool, sizeof...(uDims)> DimBitArray{uDims...};
    };

    namespace ValueSequential {
        template <typename TValueSeq, auto val>
        struct Contains_;

        template <template <auto...> class TValueCont, auto val, auto... vals>
        struct Contains_<TValueCont<vals...>, val> {
            constexpr static bool value = ((vals == val) || ...);
        };

        template <typename TValueSeq, auto val>
        constexpr static bool Contains = Contains_<TValueSeq, val>::value;
    };  // namespace ValueSequential

    namespace OperTile {
        template <typename TIndexes, typename TDimArray>
        struct DimArrToBitHelper_;

        template <typename TDimArray, size_t... I>
        struct DimArrToBitHelper_<std::index_sequence<I...>, TDimArray> {
            using type = PDimBitArrayIs<ValueSequential::Contains<TDimArray, I>...>;
        };
    }  // namespace OperTile
}  // namespace MetaNN

template <size_t AimDim>
struct Student {
    using type = typename MetaNN::OperTile::DimArrToBitHelper_<std::make_index_sequence<AimDim>,
                                                               MetaNN::PDimArrayIs<1, 2, 3>>::type;
};

int main() {
    typedef Student<10>::type Type;
    echo<Type>();
}
