/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_MATRIX_H
#define MINILA_MATRIX_H

#include "base.h"

namespace minila {

    template<typename T>
    class Matrix {

    public:
        friend class Matrix;

        Matrix() : _data(BaseArray<T>()), _rows(0), _cols(0) {}

        Matrix(const Matrix<T> &right);

        explicit Matrix(BaseArray<T> &right);

        Matrix(uint64_t rows, uint64_t cols);

        T &operator()(uint64_t row, uint64_t col);

        Matrix<T> operator+(const Matrix<T> &right);

        Matrix<T> operator-(const Matrix<T> &right);

        uint64_t rows();

        uint64_t cols();

        T *data();

    private:
        BaseArray<T> _data;
        uint64_t _rows, _cols;

    };

    template<typename T>
    Matrix<T>::Matrix(const Matrix<T> &right) {
        _rows = right._rows;
        _cols = right._cols;
        _data = right._data;
    }

    template<typename T>
    Matrix<T>::Matrix(uint64_t rows, uint64_t cols) {
        _rows = rows;
        _cols = cols;
        _data = BaseArray<T>({rows, cols});
    }

    template<typename T>
    T &Matrix<T>::operator()(uint64_t row, uint64_t col) {
        return _data({row - 1, col - 1});
    }

    template<typename T>
    uint64_t Matrix<T>::rows() {
        return _rows;
    }

    template<typename T>
    uint64_t Matrix<T>::cols() {
        return _cols;
    }

    template<typename T>
    T *Matrix<T>::data() {
        return _data.data();
    }

    template<typename T>
    Matrix<T>::Matrix(BaseArray<T> &right) {
        _rows = right[0];
        _cols = right[1];
        _data = right;
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator+(const Matrix<T> &right) {
        auto result = _data + right._data;
        return Matrix<T>(result);
    }

    template<typename T>
    Matrix<T> Matrix<T>::operator-(const Matrix<T> &right) {
        auto result = _data - right._data;
        return Matrix<T>(result);
    }

};

#endif //MINILA_MATRIX_H
