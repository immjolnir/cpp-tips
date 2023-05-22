#include <cxxabi.h>

#include <type_traits>
#include <utility>  // index_sequence

// Use fstream for std::ofstream
// https://stackoverflow.com/questions/1057287/ofstream-error-in-c
#include <fstream> 
#include <iostream>
#include <string>

namespace io
{
    class IOSave {
      public:
        IOSave(const std::string& save_file) {
            _ofile.setstate(std::ios_base::failbit | std::ios_base::badbit);
            _ofile.open(save_file, std::ios_base::out);
        }

        template <char sep = '\t', typename... Fs>
        void addLine(Fs... f) {
            // ((_ofile << f << ""), ...);
            impl(f...);
            _ofile << '\n';
        }

      protected:
        std::ofstream _ofile;

      private:
        template <size_t I = 0, typename Head>
        void impl(Head head) {
            _ofile << (I == 0 ? "" : "\t") << head;
        }

        template <size_t I = 0, typename Head, typename... Tails>
        void impl(Head head, Tails... tails) {
            impl<I>(head);
            impl<I + 1>(tails...);
        }
    };
}  // namespace io

int main() {
    io::IOSave saver("/tmp/t.tsv");
    saver.addLine("Hello", 'a', 'b', 1, 2, 0.23, 3.14);
    saver.addLine("Hello", 'a', 'b', 1, 2, 0.23, 3.14);
}
