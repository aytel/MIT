#pragma once
#include <cstddef>
#include <algorithm>
#include <iostream>

template <class T>
class my_vector{
public:
    my_vector(): capacity_(0), size_(0), array(NULL) {
        reserve(1);
    }

    my_vector(size_t n): capacity_(0), size_(0), array(NULL) {
        resize(n);
    }

    my_vector(size_t n, const T& val): capacity_(0), size_(0), array(NULL) {
        resize(n, val);
    }

    my_vector(my_vector& other): capacity_(0), size_(0), array(NULL) {
        resize(other.size());
        for (size_t it = 0; it < size_; it++) {
            new (array + it) T(other[it]);
        }
    }

    my_vector& operator=(my_vector& other) {
        my_vector<T> temp(other);
        std::swap(capacity_, temp.capacity_);
        std::swap(size_, temp.size_);
        std::swap(array, temp.array);
        return *this;
    }

    ~my_vector() {
        dest();
        ::operator delete (array);
    }

    size_t size() const {
        return size_;
    }

    size_t capacity() const {
        return capacity_;
    }

    bool empty() const {
        return !size_;
    }

    void resize(size_t n) {
        reserve(n);
        for (size_t it = size_; it < n; it++) {
            new (array + it) T();
        }
        if (size_) {
            for (size_t it = size_ - 1; it >= n; it--) {
                array[it].~T();
            }
        }
        size_ = n;
    }

    void resize(size_t n, const T& val) {
        reserve(n);
        for (size_t it = size_; it < n; it++) {
            new (array + it) T(val);
        }
        if (size_) {
            for (size_t it = size_ - 1; it >= n; it--) {
                array[it].~T();
            }
        }
        size_ = n;
    }

    void reserve(size_t n) {
        size_t res = 1;
        while (res < n) {
            res <<= 1;
        }
        if (res <= capacity_) {
            return;
        }
        T* temp = (T*) ::operator new (sizeof(T) * res);
        if (array != NULL) {
            for (size_t it = 0; it < size_; it++) {
                new (temp + it) T(array[it]);
            }
        }
        dest();
        std::swap(temp, array);
        capacity_ = res;
        ::operator delete (temp);
    }

    T& operator[](size_t index) const {
        return array[index];
    }

    void push_back(const T& t) {
        if (size_ == capacity_) {
            reserve(2 * capacity_ + !capacity_);
        }
        new (array + size_++) T(t);
    }

    void pop_back() {
        array[--size_].~T();
    }

    void clear() {
        dest();
        size_ = 0;
    }

private:
    size_t capacity_;
    size_t size_;
    void dest() {
        for (size_t it = 0; it < size_; it++) {
            array[it].~T();
        }
    }
    T* array;
};

template<class T>
std::ostream& operator<< (std::ostream &os, const my_vector<T> &vec) {
    for (size_t it = 0; it < vec.size(); it++) {
        os << vec[it] << ' ';
    }
    return os;
}