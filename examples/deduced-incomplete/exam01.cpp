// https://stackoverflow.com/questions/61058942/too-many-arguments-to-function-stdmake-sharedvector
//
template <typename... Ts>
void f(Ts&&...) {  // replacement for std::make_shared
}

int main() {
    // Candidate template ignored: substitution failure: deduced incomplete pack <(no value)> for template parameter
    // 'Ts'
    f({1});

    f(1);  // OK
    return 0;
}
