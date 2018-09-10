#include "linq.h"
#include <math.h>
#include <assert.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <cstring>
#include <iostream>
#include <functional>

class Product {
public:
    Product(const char* name, int quantity, double price);
    Product();
    Product(const Product& other);
    void swap(Product& other);
    Product& operator=(const Product& other);
    char* get_name() const;
    int get_quantity() const;
    double get_price() const;
    bool operator==(const Product& other) const;
    bool operator!=(const Product& other) const;
    ~Product();
private:
    char *name_;
    int quantity_;
    double price_;
};

std::ostream& operator<<(std::ostream& os, const Product& p) {
    os << (p.get_name() ? p.get_name() : "empty") << " " << p.get_quantity() << " " << p.get_price();
    return os;
}

Product::Product(const char *name, int quantity, double price):
    name_(name ? new char[strlen(name) + 1]() : NULL),
    quantity_(quantity),
    price_(price) {
    if(name) {
        strcpy(name_, name);
    }
}

Product::Product():
    name_(NULL),
    quantity_(0),
    price_(0)
{ }

Product::Product(const Product &other):
    Product(other.name_, other.quantity_, other.price_)
{ }

void Product::swap(Product &other) {
    std::swap(name_, other.name_);
    std::swap(quantity_, other.quantity_);
    std::swap(price_, other.price_);
}

Product& Product::operator=(const Product& other) {
    if(this != &other) {
        Product(other).swap(*this);
    }
    return *this;
}

Product::~Product() {
    delete [] name_;
}

char* Product::get_name() const {
    return name_;
}

int Product::get_quantity() const {
    return quantity_;
}

double Product::get_price() const {
    return price_;
}


bool Product::operator==(const Product& other) const {
    return !strcmp(Product::get_name(), other.get_name()) &&
            Product::get_price() == other.get_price() &&
            Product::get_quantity() == other.get_quantity();
}

bool Product::operator!=(const Product& other) const {
    return !(*this == other);
}

template< typename T >
std::ostream& operator<<(std::ostream &os, const std::vector< T > &a) {
    for(const T& x : a) {
        os << x << " ";
    }
    return os;
}

bool operator==(const std::vector< double > &a, const std::vector< double > &b) {
    if(a.size() != b.size()) {
        return false;
    }
    for(size_t i = 0;i < a.size();i++) {
        if(fabs(a[i] - b[i]) >= 1e-9) {
            return false;
        }
    }
    return true;
}

// from

/*
drop(count)
take(count)
select(f)
until(f)
until_eq(f)
where(f)
where_neq(v)
*/

// to_vector()
// copy_to(begin, end)

void test_trivial() {

    std::vector< int > vint = {5, 1, 9, 4, -10, 13, 16, 28}, rint;
    std::vector< double > vdouble = {3.14, acos(-1.0), tan(1), sqrt(7)}, rdouble;
    std::vector< Product > vproduct = {
        {"Misha", 14, 1500},
        {"Kolya", 91, 40},
        {"Vasya", 35, 100},
        {"Masha", 43, 150},
        {"Petya", 42, 239},
        {"Oleg", 72, 1},
        {"Strange Man", -100, 0}
    }, rproduct;

    rint = from(vint.begin(), vint.end())
            .to_vector();

    rdouble = from(vdouble.begin(), vdouble.end())
            .to_vector();

    rproduct = from(vproduct.begin(), vproduct.end())
            .to_vector();

    assert(vint == rint);
    assert(vdouble == rdouble);
    assert(vproduct == rproduct);

    from(vint.begin(), vint.end())
        .copy_to(rint.begin());

    from(vdouble.begin(), vdouble.end())
        .copy_to(rdouble.begin());

    from(vproduct.begin(), vproduct.end())
        .copy_to(rproduct.begin());

    assert(vint == rint);
    assert(vdouble == rdouble);
    assert(vproduct == rproduct);

    vint.resize(3);
    vdouble.resize(3);
    vproduct.resize(2);

    from(vint.begin(), vint.end())
        .copy_to(rint.begin() + 2);

    from(vdouble.begin(), vdouble.end())
        .copy_to(rdouble.begin() + 1);

    from(vproduct.begin(), vproduct.end())
        .copy_to(rproduct.begin() + 3);

    vint = {5, 1, 5, 1, 9, 13, 16, 28};
    vdouble = {3.14, 3.14, acos(-1.0), tan(1)};
    vproduct = {
        {"Misha", 14, 1500},
        {"Kolya", 91, 40},
        {"Vasya", 35, 100},
        {"Misha", 14, 1500},
        {"Kolya", 91, 40},
        {"Oleg", 72, 1},
        {"Strange Man", -100, 0}
    };

    assert(vint == rint);
    assert(vdouble == rdouble);
    assert(vproduct == rproduct);
}

namespace NUMBER_FUNCTIONS {
    template< typename T, typename P > P zero(T x) { (void) x; return P(0); }
    template< typename T, typename P > P coef(T x) { return P(x) * P(10); }
    template< typename T, typename P > P add (T x) { return P(x) + P(5); }
    template< typename T, typename P > P sqr (T x) { return P(x) * P(x); }
    template< typename T, typename P > P cube(T x) { return P(x) * sqr< T, P >(x); }
    template< typename T, typename P > P poly(T x) { return cube< T, P >(x) * P(3) + sqr< T, P >(x) * P(-2) + P(7); }

    template< typename T, typename P >
    std::vector< std::function< T(P) > > gen_vector_f() {
        return {
            zero< T, P >,
            coef< T, P >,
            add < T, P >,
            sqr < T, P >,
            cube< T, P >,
            poly< T, P >
        };
    }

    template< typename T, typename P >
    void test(const std::vector< T > &a) {
        std::vector< std::function< T(P) > > fs = gen_vector_f< T, P >();
        std::cout << (int)fs.size() << std::endl;
        for(std::function< T(P) > f : fs) {
            std::vector< P > exp, hlp;
            for(const T &x : a) {
                exp.push_back(f(x));
            }
            hlp = from(a.begin(), a.end()).
                    template select< P >(f).
                    to_vector();
            assert(hlp == exp);
        }
    }
}

void test_single() {
    std::vector< int > vint = {5, 1, 9, 4, -10, 13, 16, 28}, rint, eint;
    std::vector< double > vdouble = {3.14, acos(-1.0), tan(1), sqrt(7)}, rdouble, edouble;
    std::vector< Product > vproduct = {
        {"Misha", 14, 1500},
        {"Kolya", 91, 40},
        {"Vasya", 35, 100},
        {"Masha", 43, 150},
        {"Petya", 42, 239},
        {"Oleg", 72, 1},
        {"Strange Man", -100, 0}
    }, rproduct, eproduct;

    // drop
    for(size_t i = 0;i <= 100;i++) {
        rint = from(vint.begin(), vint.end())
                .drop(i)
                .to_vector();
        rdouble = from(vdouble.begin(), vdouble.end())
                .drop(i)
                .to_vector();
        rproduct = from(vproduct.begin(), vproduct.end())
                .drop(i)
                .to_vector();

        eint = std::vector< int >(vint.begin() + std::min(i, vint.size()), vint.end());
        edouble = std::vector< double >(vdouble.begin() + std::min(i, vdouble.size()), vdouble.end());
        eproduct = std::vector< Product >(vproduct.begin() + std::min(i, vproduct.size()), vproduct.end());

        assert(eint == rint);
        assert(edouble == rdouble);
        assert(eproduct == rproduct);
    }

    // take

    for(size_t i = 0;i <= 100;i++) {
        rint = from(vint.begin(), vint.end())
                .take(i)
                .to_vector();
        rdouble = from(vdouble.begin(), vdouble.end())
                .take(i)
                .to_vector();
        rproduct = from(vproduct.begin(), vproduct.end())
                .take(i)
                .to_vector();

        eint = std::vector< int >(vint.begin(), vint.begin() + std::min(i, vint.size()));
        edouble = std::vector< double >(vdouble.begin(), vdouble.begin() + std::min(i, vdouble.size()));
        eproduct = std::vector< Product >(vproduct.begin(), vproduct.begin() + std::min(i, vproduct.size()));

        assert(eint == rint);
        assert(edouble == rdouble);
        assert(eproduct == rproduct);
    }

    // select

    NUMBER_FUNCTIONS::test< int, int >(vint);
    NUMBER_FUNCTIONS::test< int, double >(vint);
    NUMBER_FUNCTIONS::test< double, int >(vdouble);
    NUMBER_FUNCTIONS::test< double, double >(vdouble);

    rint = from(vproduct.begin(), vproduct.end())
            .select< int >([](const Product &x) {return x.get_quantity() * x.get_price();})
            .to_vector();

    eint = {
        21000, 3640, 3500, 6450, 10038, 72, 0
    };

    assert(rint == eint);

    // until

    rint = from(vint.begin(), vint.end())
            .until([](int x){return !(x & 1);})
            .to_vector();

    rdouble = from(vdouble.begin(), vdouble.end())
            .until([](double x){return !(fabs(3.14 - x) < 1e-1);})
            .to_vector();

    rproduct = from(vproduct.begin(), vproduct.end())
            .until([](const Product &x){return !(x.get_quantity() % 5);})
            .to_vector();

    eint = {5, 1, 9};
    edouble = {3.14, acos(-1.0)};
    eproduct = {
        {"Misha", 14, 1500},
        {"Kolya", 91, 40}
    };

    assert(eint == rint);
    assert(edouble == rdouble);
    assert(eproduct == rproduct);

    // until_eq

    for(size_t i = 0;i < vint.size();i++) {
        rint = from(vint.begin(), vint.end())
                .until_eq(vint[i])
                .to_vector();
        eint = std::vector< int >(vint.begin(), vint.begin() + i);
        assert(eint == rint);
    }

    srand(42);
    for(int i = 0;i < 10;i++) {
        int x = rand() % 20;
        size_t j = 0;
        while(j < vint.size() && vint[j] != x) j++;
        rint = from(vint.begin(), vint.end())
                .until_eq(x)
                .to_vector();
        eint = std::vector< int >(vint.begin(), vint.begin() + j);
        assert(eint == rint);
    }

    for(size_t i = 0;i < vproduct.size();i++) {
        rproduct = from(vproduct.begin(), vproduct.end())
                .until_eq(vproduct[i])
                .to_vector();
        eproduct = std::vector< Product >(vproduct.begin(), vproduct.begin() + i);
        assert(eproduct == rproduct);
    }

    // where

    rint = from(vint.begin(), vint.end()).
            where([](int x){ int y = 0; while(y * y < x) y++; return y * y == x; })
            .to_vector();

    eint = {1, 9, 4, 16};

    assert(eint == rint);

    rproduct = from(vproduct.begin(), vproduct.end())
            .where([](const Product &x){char *s = x.get_name();return strlen(s) > 0 && s[0] == 'M';})
            .to_vector();

    eproduct = {
        {"Misha", 14, 1500},
        {"Masha", 43, 150}
    };

    assert(rproduct == eproduct);

    // where neq

    rint = from(vint.begin(), vint.end())
            .where_neq(100500).
            to_vector();

    assert(rint == vint);
}

void ex1() {
    std::stringstream ss("1 2 3 4 5 6 7 8 3 2 4 7 16 7 4 73 64 128 73 64 2 16"), oss;
    std::vector< int > rint, eint;
    std::istream_iterator< int > in(ss), eof;
    std::ostream_iterator< int > out(oss, " ");

    from(in, eof)
        .until([](int x){return x >= 100;})
        .where([](int x){return !(x & (x - 1));}) // только степени двойки
        .select([](int x){int res = 0;while(x > 0) res += x % 10, x /= 10; return res;})
        .copy_to(out);

    assert(oss.str() == "1 2 4 8 2 4 7 4 10 ");
}

void ex2() {
    std::vector< Product > vproduct = {
        {"Misha", 53, 1500},
        {"Kolya", 91, 40},
        {"Vasya", 35, 100},
        {"Masha", 43, 150},
        {"Petya", 42, 239},
        {"Oleg", 72, 1},
        {"Strange Man", -100, 0}
    }, rproduct, eproduct;

    rproduct = from(vproduct.begin(), vproduct.end())
            .where([](const Product &x){return x.get_quantity() > 40;})
            .until_eq(vproduct[4])
            .until_eq(Product("", 0, 0))
            .until_eq(Product("", 0, 0))
            .until_eq(Product("", 0, 0))
            .until_eq(Product("", 0, 0))
            .until_eq(Product("", 0, 0))
            .drop(1).take(1)
            .select([](const Product &x){
                std::string hlp = x.get_name();
                hlp = "super " + hlp;
                return Product(hlp.c_str(), x.get_quantity(), x.get_price());
            })
            .to_vector();

    eproduct = {
        {"super Kolya", 91, 40}
    };

    assert(eproduct == rproduct);
}

#include <map>
//#include <set>

std::map< int, int > mp;

class Counter {
public:
    Counter() = default;
    Counter(int field_):
        field(field_)
    { }
    Counter(const Counter &other):
        field(other.field) {
        count++;
        mp[field]++;
    }
    Counter& operator=(const Counter &other) {
        if(this != &other) {
            field = other.field;
            count++;
            mp[field]++;
        }
        return *this;
    }
    static int get_count() {
        return count;
    }
    int get_field() const {
        return field;
    }
    bool operator==(const Counter &other) const {
        return get_field() == other.get_field();
    }
    bool operator!=(const Counter &other) const {
        return !(*this == other);
    }
private:
    int field = 0;
    static int count;
};

int Counter::count = 0;

std::ostream& operator<<(std::ostream& os, const Counter &x) {
    os << "C(" << x.get_field() << ") ";
    return os;
}

void ex3() {
    std::vector< Counter > a = {
        {5}, {9}, {4}, {3}, {2}, {7}, {19}, {13}, {17}, {18}
    }, b;
    Counter y(100500);

    b = from(a.begin(), a.end())
        .until([](const Counter &x){return x.get_field() > 100;})
        .until_eq(a[6])
        .where([](const Counter &x){return x.get_field() % 2;})
        .where_neq(y)
        .drop(1).take(1e5)
        .select([](const Counter &x){return Counter(x.get_field() * 100 );})
        .to_vector();

    std::cout << "count = " << Counter::get_count() << ", b = " << b << std::endl;

    for(std::pair< int, int > pr : mp) {
        std::cout << pr.first << " " << pr.second << std::endl;
    }
}

void test_composition() {
    ex1();
    ex2();
    ex3();
}

int main() {

    test_trivial();
    test_single();
    test_composition();

    return 0;
}
