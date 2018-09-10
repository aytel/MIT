#include <iostream>
#include <cstring>
#include <cassert>

#include "my_vector.h"

class Product {
public:
    Product(const char *src, int quantity, double price): quantity_(quantity), price_(price) {
        name_ = new char[strlen(src) + 1];
        strcpy(name_, src);
    }

    Product(){
        name_ = new char[1];
        name_[0] = '\0';
        quantity_ = price_ = 0;
    }

    ~Product(){
        delete[] name_;
    }

    Product(const Product &other): quantity_(other.quantity_), price_(other.price_) {
        name_ = new char[strlen(other.name_) + 1];
        strcpy(name_, other.name_);
    }

    Product& operator=(const Product &other) {
        Product tmp(other);
        std::swap(name_, tmp.name_);
        std::swap(quantity_, tmp.quantity_);
        std::swap(price_, tmp.price_);
        return *this;
    }

    const char* name() const {
        return name_;
    }
    int quantity() const {
        return quantity_;
    }
    double price() const {
        return price_;
    }

    bool operator==(const Product &other) const {
        return !strcmp(name_, other.name_) && (price_ == other.price_) && (quantity_ == other.quantity_);
    }

    bool operator!=(const Product &other) const {
        return !(*this == other);
    }

private:
    char* name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream &os, Product &val) {
    os << val.name() << ' ' << val.quantity() << ' ' << val.price();
    return os;
}

void print(const my_vector<Product>& v) {
    std::cout << v << std::endl;
}

template<class T>
void test_my_vector(const T& v1, const T& v2) {
    my_vector<T> vec;

    vec.resize(1, v1);
    if (vec.size() != 1 || vec[0] != v1) {
        std::cerr << "resize not OK\n";
        exit(1);
    }
    std::cerr << "resize OK\n";

    vec.push_back(v2);
    if (vec.size() != 2 || vec[1] != v2) {
        std::cerr << "push_back not OK\n";
        exit(1);
    }
    std::cerr << "push_back OK\n";

    vec.pop_back();
    if (vec.size() != 1) {
        std::cerr << "pop_back not OK\n";
        exit(1);
    }
    std::cerr << "pop_back OK\n";

    vec.reserve(20);
    if (vec.capacity() != 32) {
        std::cerr << "reserve not OK\n";
        exit(1);
    }
    std::cerr << "reserve OK\n";

    vec.clear();
}

int main() {

    test_my_vector<int>(5, 10);
    test_my_vector<Product>(Product("asdf", 4, 12.0), Product("qwe", -1, 7.5));

    my_vector<Product> v(10);
    v = v;
    
    return 0;
}