#include <iostream>
#include <memory>  // std::allocator
#include <type_traits>
#include <vector>

namespace dts
{

    template <typename ContainerAllocator>
    struct CompressedImage_ {
        int header;
        int format;

        // typedef std::vector<uint8_t, typename std::allocator_traits<ContainerAllocator>::template
        // rebind_alloc<uint8_t>>
        //   _data_type;
        std::vector<uint32_t> data;

        CompressedImage_(int h_, int f_, const std::vector<uint32_t>& data_) : header(h_), format(f_), data(data_) {
            std::cout << "default ctor" << std::endl;
        }

        CompressedImage_(const CompressedImage_& other) {
            header = other.header;
            format = other.format;
            data = other.data;
            std::cout << "copy ctor" << std::endl;
        }

        typedef std::shared_ptr<CompressedImage_<ContainerAllocator>> Ptr;
        typedef std::shared_ptr<CompressedImage_<ContainerAllocator> const> ConstPtr;
    };

    typedef CompressedImage_<std::allocator<void>> CompressedImage;

    // constants requiring out of line definition

    template <typename ContainerAllocator>
    std::ostream& operator<<(std::ostream& s, const CompressedImage_<ContainerAllocator>& v) {
        // ros::message_operations::Printer<CompressedImage_<ContainerAllocator> >::stream(s, "", v);
        s << "[ header=" << v.header << ", format=" << v.format << ", data=[";
        for (auto& i : v.data) s << i << ", ";

        s << "].";
        return s;
    }

    template <typename ContainerAllocator1, typename ContainerAllocator2>
    bool operator==(const CompressedImage_<ContainerAllocator1>& lhs,
                    const CompressedImage_<ContainerAllocator2>& rhs) {
        return lhs.header == rhs.header && lhs.format == rhs.format && lhs.data == rhs.data;
    }

    template <typename ContainerAllocator1, typename ContainerAllocator2>
    bool operator!=(const CompressedImage_<ContainerAllocator1>& lhs,
                    const CompressedImage_<ContainerAllocator2>& rhs) {
        return !(lhs == rhs);
    }
}  // namespace dts

int main() {
    std::cout << "aggregate type?" << (std::is_aggregate_v<dts::CompressedImage> ? "yes" : "no") << std::endl;

    dts::CompressedImage::ConstPtr ptr;
    ptr.reset(new dts::CompressedImage{1, 2, {3, 4, 5}});  // std::make_shared is not working.
    // std::make_shared<dts::CompressedImage const>(new dts::CompressedImage{1, 2, {3, 4, 5}});
    // assignment of member ‘dts::CompressedImage_<std::allocator<void> >::header’ in read-only object
    // ptr->header = 1;
    // ptr->format = 2;
    // ptr->data = {3, 4, 5};
    std::cout << *ptr << std::endl;

    // error: cannot assign to return value because function 'operator->' returns a const value
    // ptr->header = 2;

    // The ptr is ConstPtr, alought we cannot modify its data but we could reset it.
    ptr.reset(new dts::CompressedImage{10, 20, {30, 40, 50}});
    std::cout << *ptr << std::endl;

    dts::CompressedImage img{100, 200, {300, 400, 500}};
    std::cout << img << std::endl;

    // free(): double free detected in tcache 2
    // ptr.reset(&img); // shared_ptr can only be used with new object.

    auto old = ptr;
    ptr.reset(new dts::CompressedImage(img));  // default copy ctor
    std::cout << *ptr << std::endl;

    std::cout << "OLD:\n" << *old << std::endl;

    return 0;
}
