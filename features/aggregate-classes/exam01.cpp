#include <iostream>
#include <new>
#include <type_traits>
#include <utility>

// constructs a T at the uninitialized memory pointed to by p using
// list-initialization for aggregates and non-list initialization otherwise
template <class T, class... Args>
T* construct(T* p, Args&&... args) {
    if constexpr (std::is_aggregate_v<T>)
        return ::new (static_cast<void*>(p)) T{std::forward<Args>(args)...};
    else
        return ::new (static_cast<void*>(p)) T(std::forward<Args>(args)...);
}

struct A {
    int x, y;
};

struct B {
    B(int index_, const char* data_) : index(index_), data{data_} {}

    int index;
    const char* data;
};

int main() {
    std::cout << "A is aggregate type? " << (std::is_aggregate_v<A> == true ? "yes" : "no") << "\n";
    std::cout << "B is aggregate type? " << (std::is_aggregate_v<B> == true ? "yes" : "no") << "\n";

    std::aligned_union_t<1, A, B> storage;
    [[maybe_unused]] A* a = construct(reinterpret_cast<A*>(&storage), 1, 2);
    [[maybe_unused]] B* b = construct(reinterpret_cast<B*>(&storage), 1, "hello");

    std::cout << "Point A: x=" << a->x << ", y=" << a->y << std::endl;
    std::cout << "Point B: index=" << b->index << ", data=" << b->data << std::endl;

    return 0;
}
