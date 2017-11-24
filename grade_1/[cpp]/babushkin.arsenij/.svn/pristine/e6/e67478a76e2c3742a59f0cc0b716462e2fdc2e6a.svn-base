#include <algorithm>
#include <cstring>
#include "matrix.h"

void Matrix::swap(Matrix &m) {
    std::swap(rows, m.rows);
    std::swap(cols, m.cols);
    std::swap(data, m.data);
}

Matrix::Matrix(std::size_t r, std::size_t c): rows(r), cols(c) {
    data = new int* [rows];
    int *temp = new int [rows * cols] ();
    for (std::size_t i = 0; i < rows; i++) {
        data[i] = temp + i * cols;
    }
}

Matrix::Matrix(Matrix &m): rows(m.rows), cols(m.cols) {
    data = new int* [rows];
    int *temp = new int [rows * cols] ();
    for (std::size_t i = 0; i < rows; i++) {
        data[i] = temp + i * cols;
    }
    memcpy(data[0], m.data[0], rows * cols * sizeof(int));
}

Matrix::~Matrix(){
    delete [] data[0];
    delete [] data;
}

std::size_t Matrix::get_rows() { return rows; }
std::size_t Matrix::get_cols() { return cols; }

void Matrix::set(std::size_t i, std::size_t j, int val) {
    data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) {
  return data[i][j];
}

void Matrix::print(FILE* f) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            fprintf(f, "%d ", data[i][j]);
        }
        fprintf(f, "\n");
    }
}

bool Matrix::operator==(Matrix& m) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            if (data[i][j] != m.data[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

bool Matrix::operator!=(Matrix& m) {
    return !(*(this) == m);
}

Matrix& Matrix::operator+=(Matrix& m) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            data[i][j] += m.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(Matrix& m) {
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < cols; j++) {
            data[i][j] -= m.data[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(Matrix& m) {
    Matrix temp(rows, m.cols);
    for (std::size_t i = 0; i < rows; i++) {
        for (std::size_t j = 0; j < m.cols; j++) {
            for (std::size_t k = 0; k < cols; k++) {
                temp.data[i][j] += data[i][k] * m.data[k][j];
            }
        }
    }
    std::swap(*this, temp);
    return *this;
}

Matrix& Matrix::operator=(Matrix &m) {
    Matrix temp(m);
    swap(temp);
    return *this;
}

Matrix Matrix::operator+(Matrix& m) {   
    Matrix temp(*this);
    return temp += m;
}

Matrix Matrix::operator-(Matrix& m) {
    Matrix temp(*this);
    return temp -= m;
}

Matrix Matrix::operator*(Matrix& m) {
    Matrix temp(*this);
    return temp *= m;
}   