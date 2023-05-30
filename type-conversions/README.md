# Type Conversions

## function-to-pointer

## shared-ptr
* exam00.cpp: Demostrate the usages of `static_point_cast` and `dynamic_pointer_cast`.
    * `dynamic_pointer_cast` probably returns a nullptr when convertion fails.

* exam04.cpp: cast `std::shared_ptr<Derived>` to `std::shared_ptr<const Base>` implicitly.

* exam01.cpp: Convert an object of `std::shared_ptr<const T>` to `std::shared_ptr<T>`.

* exam02.cpp: Convert the shard_ptr<T> to shared_ptr<const T> easily.

* exam03.cpp: Convertion betweed std::shared_ptr and boost::shared_ptr. The key is the new pt holds the original ptr'copy in his lifetime.