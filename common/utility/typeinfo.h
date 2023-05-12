#include <cxxabi.h>
#include <sstream>
#include <string>
#include <typeinfo>  // for typeid

namespace utility {
    template <typename T>
    std::string typeInfo(T& t) {
        int status;
        char* realname;
        const std::type_info& ti = typeid(t);
        realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
        std::stringstream ss;
        ss << "Type Signature: " << ti.name() << "\t=> " << realname << "\t: " << status;
        return ss.str();
    }

    template <typename T>
    std::string typeInfo() {
        int status;
        char* realname;
        const std::type_info& ti = typeid(T);
        realname = abi::__cxa_demangle(ti.name(), NULL, NULL, &status);
        std::stringstream ss;
        ss << "Type Signature: " << ti.name() << "\t=> " << realname << "\t: " << status;
        return ss.str();
    }

}  // namespace utility
