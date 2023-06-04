/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_LINSOLVE_H
#define MINILA_LINSOLVE_H

#include <lapacke.h>
#include <stdexcept>
#include "matrix.h"
#include "vector.h"

namespace minila {
    // Simple functions to solve linear systems of square matrices.

    template<typename T>
    Matrix<T> linsolve(Matrix<T> &left, Matrix<T> &right) {
        throw std::runtime_error("Unsupported type for linsolve.");
    }

    template<>
    Matrix<float> linsolve(Matrix<float> &left, Matrix<float> &right) {

    }

    template<>
    Matrix<double> linsolve(Matrix<double> &left, Matrix<double> &right) {

    }

};

#endif //MINILA_LINSOLVE_H
