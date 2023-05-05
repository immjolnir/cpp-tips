/*
 * https://cppinsights.io/
 * After insight, the main() becomes empty.
 *
 * */
#include <iostream>
#include <string>

struct Foo {
    int hello() { return 0; }
};

struct Bar {
    int hello(int i) { return i + 1; }
};

struct FooDog {
    int hello() { return 0; }
    int hello(int i) { return i + 1; }
    int hello(int i, const std::string& str) { return i + 1; }
};

struct Baz {
    int who() { return 1; }
};

// SFINAE test
template <typename T>
class has_hello {
    typedef char One;
    struct Two {
        char x[2];
    };

    template <typename C>
    static One test(decltype(&C::hello));

    // If some confused about ..., look
    // https://stackoverflow.com/questions/39664453/variadic-function-without-named-argument
    template <typename C>
    static Two test(...);

   public:
    enum { value = (sizeof(test<T>(0)) == sizeof(char)) };
};

int main(int argc, char* argv[]) {
    static_assert(has_hello<Foo>::value, "Foo should has hello method");
    static_assert(has_hello<Bar>::value, "Bar should has hello method");

    // error: static assertion failed: FooDog hasn't hello method
    // static_assert(has_hello<FooDog>::value, "FooDog hasn't hello method");

    // It is caused by overloaded method, for example:
    // error: decltype cannot resolve address of overloaded function
    // decltype(&FooDog::hello) t __attribute__((unused));

    static_assert(!has_hello<Baz>::value, "Baz shouldn't have hello method");

    return 0;
}
