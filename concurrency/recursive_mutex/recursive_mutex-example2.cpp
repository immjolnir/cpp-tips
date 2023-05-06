/*
 * https://medium.com/@simontoth/daily-bit-e-of-c-std-recursive-mutex-dd9b84f38f8d
 *
The std::recursive_mutex is a std::mutex variant that permits one thread to hold multiple locks. Only once all locks are released can other threads acquire this mutex.

This feature comes in handy when designing thread-safe data structures.
 * */
#include <algorithm>
#include <chrono>
#include <iostream>
#include <mutex>
#include <span>
#include <thread>

struct NonRecursive {
    void push_back(int value) {
        std::unique_lock<std::mutex> lock(mux_);
        // We already hold mux_, so we couldn't call reserve()
        if (size_ == capacity_) reserve_impl(capacity_ == 0 ? 64 : capacity_ * 2);
        data_[size_++] = value;
    }
    void reserve(size_t cnt) {
        std::unique_lock<std::mutex> lock(mux_);
        reserve_impl(cnt);
    }

  private:
    // reserve_impl expects mux_ to be held by the caller
    void reserve_impl(size_t cnt) {
        auto new_data = std::make_unique<int[]>(cnt);
        std::ranges::copy(std::span(data_.get(), size_), new_data.get());
        data_ = std::move(new_data);
        capacity_ = cnt;
        size_ = std::min(size_, capacity_);
    }

  private:
    std::mutex mux_;
    std::unique_ptr<int[]> data_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

struct Recursive {
    void push_back(int value) {
        std::unique_lock<std::recursive_mutex> lock(mux_);
        // holding a recursive mutex multiple times is fine
        if (size_ == capacity_) reserve(capacity_ == 0 ? 64 : capacity_ * 2);
        data_[size_++] = value;
    }
    void reserve(size_t cnt) {
        std::unique_lock<std::recursive_mutex> lock(mux_);
        auto new_data = std::make_unique<int[]>(cnt);
        std::ranges::copy(std::span(data_.get(), size_), new_data.get());
        data_ = std::move(new_data);
        capacity_ = cnt;
        size_ = std::min(size_, capacity_);
    }

  private:
    std::recursive_mutex mux_;
    std::unique_ptr<int[]> data_;
    size_t size_ = 0;
    size_t capacity_ = 0;
};

int main() {
    {  // Non-recursive case
        NonRecursive non;
        for (int i = 0; i < 200; i++) {
            non.push_back(i);
        }
        non.reserve(2);
    }

    {  // recusive lock
        Recursive rec;
        for (int i = 0; i < 200; i++) {
            rec.push_back(i);
        }
        rec.reserve(2);
    }
}
