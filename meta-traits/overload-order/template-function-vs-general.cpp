#include <iostream>

struct Student {
    template <typename I, typename J>
    void echo(I i, J j) {
        std::cout << "Template Function: i=" << i << ", j=" << j << std::endl;
    }

    void echo(int i, double j) { std::cout << "General Function: i=" << i << ", j=" << j << std::endl; }
};

int main() {
    Student st;

    st.echo(1, 2.1);  // General function: i=1, j=2.1
    st.echo(1.1, 2);  // Template function: i=1.1, j=2
}
