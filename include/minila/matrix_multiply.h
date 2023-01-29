/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_MATRIX_MULTIPLY_H
#define MINILA_MATRIX_MULTIPLY_H

#include "matrix.h"

namespace minila::lapack {

    template<typename T>
    Matrix<T> multiply(Matrix<T> &left, Matrix<T> &right) {
        throw std::runtime_error("Unsupported type for lapack::multiply.");
    }

    template<>
    Matrix<float> multiply<float>(Matrix<float> &left, Matrix<float> &right) {
        return Matrix<float>(2, 2);
    }

    template<>
    Matrix<double> multiply<double>(Matrix<double> &left, Matrix<double> &right) {
        return Matrix<double>(2, 2);
    }

};

#endif //MINILA_MATRIX_MULTIPLY_H
