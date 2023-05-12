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

namespace MetaNN::NSDotLayer {

template <size_t... uDims>
struct PDimArrayIs {
    static constexpr std::array<size_t, sizeof...(uDims)> DimArray{uDims...};
};

template <typename TIndexArr, size_t uModDim>
struct ModeDim2PermuteArrHelper_;

template <size_t... I, size_t uModDim>
struct ModeDim2PermuteArrHelper_<std::index_sequence<I...>, uModDim> {
    constexpr static size_t dimLen = sizeof...(I);
    using type = PDimArrayIs<((I + uModDim) % dimLen)...>;
};

template <size_t uDim, size_t uModDim>
struct ModeDim2PermuteArr_ {
    using type = typename ModeDim2PermuteArrHelper_<std::make_index_sequence<uDim>, uModDim>::type;
};
}  // namespace MetaNN::NSDotLayer

template <size_t DimNum, size_t modDimNum>
struct Student {
    using Permute1 = typename MetaNN::NSDotLayer::ModeDim2PermuteArr_<DimNum, modDimNum>::type;
};

int main() {
    typedef Student<15, 3>::Permute1 Type;
    echo<Type>();

    // clang-format off
    /** 
    /usr/bin/ld: /tmp/cch69wLK.o: warning: relocation against `_ZN6MetaNN10NSDotLayer11PDimArrayIsIJLm3ELm4ELm5ELm6ELm7ELm8ELm9ELm10ELm11ELm12ELm13ELm14ELm0ELm1ELm2EEE8DimArrayE' in read-only section `.text'
    /usr/bin/ld: /tmp/cch69wLK.o: in function `main':
    index_sequence.cpp:(.text+0x14): undefined reference to `MetaNN::NSDotLayer::PDimArrayIs<3ul, 4ul, 5ul, 6ul, 7ul, 8ul, 9ul, 10ul, 11ul, 12ul, 13ul, 14ul, 0ul, 1ul, 2ul>::DimArray'
    /usr/bin/ld: warning: creating DT_TEXTREL in a PIE
    collect2: error: ld returned 1 exit status
    */
    // clang-format on
    // It will raise the link error as above.
    // for (auto& t : Type::DimArray) {
    //     std::cout << t << std::endl;
    // }
}
