#pragma once
#include <iostream>
#include <tuple>
#include <algorithm>
#include <vector>

class MatrixException {
public:
    MatrixException(){}
    ~MatrixException(){}
    virtual const char* what() = 0;
};
class AddException : public MatrixException {
public:
    AddException(){}
    ~AddException(){}
    const char* what() override;
};
class MulException : public MatrixException {
public:
    MulException(){}
    ~MulException(){}
    const char* what() override;
};
class AccException : public MatrixException {
public:
    AccException(){}
    ~AccException(){}
    const char* what() override;
};

class ref {
public:
    ref(std::vector<int>& data, int m): data(data), m(m){}
    ~ref(){}
    operator std::vector<int>&();
    int& operator[](int y);
private:
    std::vector<int>& data;
    int m;
};

class Matrix {
public:
    Matrix(): n(0), m(0), data(std::vector<std::vector<int>>()){}
    Matrix(int n, int m): n(n), m(m), data(std::vector<std::vector<int>>(n, std::vector<int>(m, 0))){}
    ~Matrix();
    Matrix(const Matrix &ot): n(ot.n), m(ot.m), data(ot.data){}
    Matrix& operator=(const Matrix &ot);
    ref operator[](int x);
    Matrix& operator+=(Matrix& ot);
    Matrix& operator*=(Matrix& ot);
    int R() const;
    int C() const;
private:
    int n, m;
    std::vector<std::vector<int>> data;
};

std::istream& operator>>(std::istream &is, Matrix& mt);

std::ostream& operator<<(std::ostream &os, Matrix& mt);