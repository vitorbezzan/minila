/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_MATRIX_H
#define MINILA_MATRIX_H

#include "base.h"

namespace minila {

    template<typename Type>
    class Matrix {

    public:
        friend class Matrix;

        Matrix() : _data(BaseArray<Type>()), _rows(0), _cols(0) {}
        Matrix(const Matrix<Type> &right);
        explicit Matrix(BaseArray<Type> &right);
        Matrix(uint64_t rows, uint64_t cols);

        Type &operator()(uint64_t row, uint64_t col);
        Matrix<Type> operator+(const Matrix<Type> &right);
        Matrix<Type> operator-(const Matrix<Type> &right);

        const uint64_t rows();
        const uint64_t cols();

    private:
        BaseArray<Type> _data;
        uint64_t _rows, _cols;

    };

    template<typename Type>
    Matrix<Type>::Matrix(const Matrix<Type> &right) {
        _rows = right._rows;
        _cols = right._cols;
        _data = right._data;
    }

    template<typename Type>
    Matrix<Type>::Matrix(uint64_t rows, uint64_t cols) {
        _rows = rows;
        _cols = cols;
        _data = BaseArray<Type>({rows, cols});
    }

    template<typename Type>
    Type &Matrix<Type>::operator()(uint64_t row, uint64_t col) {
        return _data({row - 1, col - 1});
    }

    template<typename Type>
    const uint64_t Matrix<Type>::rows() {
        return _rows;
    }

    template<typename Type>
    const uint64_t Matrix<Type>::cols() {
        return _cols;
    }

    template<typename Type>
    Matrix<Type>::Matrix(BaseArray<Type> &right) {
        _rows = right[0];
        _cols = right[1];
        _data = right;
    }

    template<typename Type>
    Matrix<Type> Matrix<Type>::operator+(const Matrix<Type> &right) {
        auto result = _data + right._data;
        return Matrix < Type > (result);
    }

    template<typename Type>
    Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &right) {
        auto result = _data - right._data;
        return Matrix < Type > (result);
    }

};

#endif //MINILA_MATRIX_H
