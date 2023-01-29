/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_MATRIX_H
#define MINILA_MATRIX_H

#include <cblas.h>
#include <stdexcept>
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

        uint64_t rows();
        uint64_t cols();

        Type *data();

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
    uint64_t Matrix<Type>::rows() {
        return _rows;
    }

    template<typename Type>
    uint64_t Matrix<Type>::cols() {
        return _cols;
    }

    template<typename Type>
    Type *Matrix<Type>::data() {
        return _data.data();
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
        return Matrix<Type>(result);
    }

    template<typename Type>
    Matrix<Type> Matrix<Type>::operator-(const Matrix<Type> &right) {
        auto result = _data - right._data;
        return Matrix<Type>(result);
    }

    namespace naive {

        // This naive algorithm accepts different multiplication types
        template<typename T1, typename T2>
        auto multiply(Matrix<T1> &left, Matrix<T2> &right) {

            auto cols = left.cols();
            auto rows = right.rows();

            if (cols != rows)
                throw std::invalid_argument("Invalid axis sizes on operation multiply.");

            using R = decltype(T1(0) + T2(0));
            Matrix<R> result(left.rows(), right.cols());

            for (uint64_t i = 1; i <= result.rows(); i++)
                for (uint64_t k = 1; k <= cols; k++)
                    for (uint64_t j = 1; j <= result.cols(); j++)
                        result(i, j) += left(i, k) * right(k, j);

            return result;
        }
    };
};

#endif //MINILA_MATRIX_H
