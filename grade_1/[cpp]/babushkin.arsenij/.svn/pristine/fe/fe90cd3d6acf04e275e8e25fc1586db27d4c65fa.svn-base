#include "matrix.h"

const char* AddException::what() {
    return "ADD: dimensions do not match.\n";
}

const char* AccException::what() {
    return "ACCESS: bad index.\n";
}

const char* MulException::what() {
    return "MUL: #arg1.columns != #arg2.rows.\n";
}

ref::operator std::vector<int>&() {
    return data;
}

int& ref::operator[](int y) {
    if (y >= m || y < 0) {
        throw AccException();
    }
    return data[y];
}

Matrix::~Matrix() {
    //data.~std::vector<std::vector<int>>();
}

Matrix& Matrix::operator=(const Matrix& ot) {
    Matrix temp(ot);
    std::swap(n, temp.n);
    std::swap(m, temp.m);
    std::swap(data, temp.data);
    return *this;
}

ref Matrix::operator[](int x) {
    if (x >= n || x < 0) {
        throw AccException();
    }
    return ref(data[x], m);
}

Matrix& Matrix::operator+=(Matrix& ot) {
    if (n != ot.n || m != ot.m) {
        throw AddException();
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            (*this)[i][j] += ot[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(Matrix& ot) {
    if (m != ot.n) {
        throw MulException();
    }
    Matrix temp(n, ot.m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < ot.m; j++) {
            for (int k = 0; k < m; k++) {
                temp[i][j] += (*this)[i][k] * ot[k][j];
            }
        }
    }
    return *this = temp;
}

int Matrix::R() const {
    return n;
}

int Matrix::C() const {
    return m;
}

std::istream& operator>>(std::istream &is, Matrix& mt) {
    int n, m;
    is >> n >> m;
    Matrix temp(n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            is >> temp[i][j];
        }
    }
    mt = temp;
    return is;
}

std::ostream& operator<<(std::ostream &os, Matrix& mt) {
    for (int i = 0; i < mt.R(); i++) {
        for (int j = 0; j < mt.C(); j++) {
            os << mt[i][j] << ' ';
        }
        os << '\n';
    }
    return os;
}