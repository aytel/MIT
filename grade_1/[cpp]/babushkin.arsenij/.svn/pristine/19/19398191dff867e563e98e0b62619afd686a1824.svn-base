#ifndef LINQ_H_
#define LINQ_H_

#include <utility>
#include <vector>
#include <functional>
#include <iostream>

template<typename T, typename Iter>
class range_enumerator;
template<typename T>
class drop_enumerator;
template<typename T>
class take_enumerator;
template<typename T, typename U, typename F>
class select_enumerator;
template<typename T, typename F>
class until_enumerator;
template<typename T, typename F>
class where_enumerator;

template<typename T>
class enumerator {
public:
    virtual const T& operator*() const = 0;
    virtual void operator++() = 0;  // Переход к следующему элементу
    virtual operator bool() const = 0;  // Возвращает true, если есть текущий элемент

    drop_enumerator<T> drop(int count) {
        return drop_enumerator<T>(*this, count);
    }

    take_enumerator<T> take(int count) {
        return take_enumerator<T>(*this, count);
    }

    template<typename U = T, typename F>
    select_enumerator<T, U, F> select(const F &func) {
        return select_enumerator<T, U, F>(*this, func);
    }

    template<typename F>
    until_enumerator<T, F> until(const F &func) {
        return until_enumerator<T, F>(*this, func);
    }

    until_enumerator<T, std::function<bool(T)>> until_eq(const T &val) {
        return until_enumerator<T, std::function<bool(T)>>(*this, [&val](const T &cur){ return cur == val; });
    }

    template<typename F>
    where_enumerator<T, F> where(const F &func) {
        return where_enumerator<T, F>(*this, func);
    }

    where_enumerator<T, std::function<bool(T)>> where_neq(const T &val) {
        return where_enumerator<T, std::function<bool(T)>>(*this, [&val](const T &cur){ return cur != val; });
    }

    std::vector<T> to_vector() {
        std::vector<T> ret;
        while (*this) {
            ret.push_back(this->operator *());
            this->operator++();
        }

        /*for (int x : ret) {
            std::cerr << x << ' ';
        }
        std::cerr << '\n';*/

        return ret;
    }

    template<typename Iter>
    void copy_to(Iter it) {
        while (*this) {
            *it = this->operator *();
            it++;
            this->operator++();
        }
    }
};

template<typename T, typename Iter>
class range_enumerator : public enumerator<T> {
public:
    range_enumerator(Iter begin, Iter end) : begin_(begin), end_(end) {}
    const T& operator *() const override {
        return *begin_;
    }
    void operator++() override {
        if (this->operator bool()) {
            begin_++;
        }
    }
    operator bool() const override {
        return begin_ != end_;
    }

private:
    Iter begin_, end_;
};

template<typename T>
auto from(T begin, T end) {
    return range_enumerator<typename std::iterator_traits<T>::value_type, T>(begin, end);
}

template<typename T>
class drop_enumerator : public enumerator<T> {
public:
    drop_enumerator(enumerator<T> &parent, int count) : parent_(parent) {
        for (int i = 0; i < count; i++) {
            ++parent_;
        }
    }
    const T& operator *() const override {
        return *parent_;
    }
    void operator++() override {
        ++parent_;
    }
    operator bool() const override {
        return parent_;
    }

private:
    enumerator<T>& parent_;
};

template<typename T>
class take_enumerator : public enumerator<T> {
public:
    take_enumerator(enumerator<T> &parent, int count) : parent_(parent), count_(count) {}
    const T& operator *() const override {
        return *parent_;
    }
    void operator++() override {
        ++parent_;
        count_--;
    }
    operator bool() const override {
        return count_ && parent_;
    }

private:
    enumerator<T>& parent_;
    int count_;
};

template<typename T, typename U, typename F>
class select_enumerator : public enumerator<U> {
public:
    select_enumerator(enumerator<T> &parent, const F &func) : parent_(parent), func_(func) , fresh(0) {}
    const U& operator *() const override {
        if (!fresh) {
            val = func_(*parent_);
            fresh = 1;    
        }
        return val;
    }
    void operator++() override {
        fresh = 0;
        ++parent_;
    }
    operator bool() const override {
        return parent_;
    }

private:
    enumerator<T>& parent_;
    const F func_;
    mutable U val;
    mutable bool fresh;
};

template<typename T, typename F>
class until_enumerator : public enumerator<T> {
public:
    until_enumerator(enumerator<T> &parent, const F &predicate) : parent_(parent), predicate_(predicate) {}
    const T& operator *() const override {
        return *parent_;
    }
    void operator++() override {
        if (*this) {
            ++parent_;
        }
    }
    operator bool() const override {
        return parent_ && !predicate_(this->operator *());
    }

private:
    enumerator<T>& parent_;
    const F predicate_;
};

template<typename T, typename F>
class where_enumerator : public enumerator<T> {
public:
    where_enumerator(enumerator<T> &parent, const F &predicate) : parent_(parent), predicate_(predicate) {
        while (parent_ && !predicate_(this->operator *())) {
            //std::cerr << "mem\n" << this->operator *() << '\n';
            ++parent_;
        }
    }
    const T& operator *() const override {
        return *parent_;
    }
    void operator++() override {
        do {
            //std::cerr << "mem\n" << this->operator *() << '\n';
            ++parent_;
        } while (parent_ && !predicate_(this->operator *()));
    }
    operator bool() const override {
        return parent_;
    }

private:
    enumerator<T>& parent_;
    const F predicate_;
};

#endif