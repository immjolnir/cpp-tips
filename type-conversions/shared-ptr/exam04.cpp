#include <iostream>
#include <memory>

struct Time {
    int sec;    // second;
    int milli;  // millisecond;
};

std::ostream& operator<<(std::ostream& out, const Time& obj) {
    out << "time[second:" << obj.sec << ", millisecond:" << obj.milli << "]";
    return out;
}

struct Base {
    typedef std::shared_ptr<Base> Ptr;
    typedef std::shared_ptr<const Base> ConstPtr;

    Time get_stereo_timestamp() const { return stereo_timestamp; }

    Time stereo_timestamp;
};

struct Derived : public Base {
    typedef std::shared_ptr<Derived> Ptr;
    typedef std::shared_ptr<const Derived> ConstPtr;

    int get_seq() const { return seq; }

    int seq;
};

std::ostream& operator<<(std::ostream& out, const Base& obj) {
    out << "Base[stereo_timestamp:" << obj.get_stereo_timestamp() << "]";
    return out;
}

std::ostream& operator<<(std::ostream& out, const Derived& obj) {
    out << "Derived[seq:" << obj.get_seq() << ", stereo_timestamp: " << obj.get_stereo_timestamp() << "]";
    return out;
}

int main() {
    Derived::Ptr derived;
    derived.reset(new Derived);
    derived->seq = 1;
    derived->stereo_timestamp = Time{1685351883, 1234};

    std::cout << *derived << std::endl;

    // cast std::shared_ptr<Derived> to std::shared_ptr<const Base>
    Base::ConstPtr base = derived;  // implicit conversions are generally safe. static_cast can make it explicitly.
    std::cout << *base << std::endl;

    // no matching function for call to ‘std::shared_ptr<Derived>::shared_ptr(Base::ConstPtr&)’
    // derived = static_cast<Derived::Ptr>(base);

    Base::Ptr base_mutable_ptr(new Base);
    base_mutable_ptr->stereo_timestamp = Time{1685351883, 4567};

    // no match for ‘operator=’ (operand types are ‘Derived::Ptr’ {aka ‘std::shared_ptr<Derived>’} and ‘Base::Ptr’ {aka
    // ‘std::shared_ptr<Base>’})
    // derived = base_mutable_ptr;

    // (source type is not polymorphic)
    // derived = std::dynamic_pointer_cast<Derived>(base_mutable_ptr);

    // Still connot convert std::shared_ptr<Base> to std::shared_ptr<Derived>
    // derived = (Derived::Ptr)base_mutable_ptr;
}
