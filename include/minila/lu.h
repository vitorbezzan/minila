/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_LU_H
#define MINILA_LU_H

#include <lapacke.h>
#include <stdexcept>
#include "constants.h"
#include "matrix.h"

namespace minila {

    template<typename T>
    struct LU {
        Matrix<T> D; // Store the decomposition
        Vector<int> ipiv; // Stores the pivoting vector

        int info = 0; // Stores the info result for calculation
    };

    template<typename T>
    LU<T> lu(Matrix<T> &M) {
        throw std::runtime_error("Unsupported type for LU.");
    }

    template<>
    LU<float> lu(Matrix<float> &M) {
        auto D = Matrix(M);
        auto ipiv = Vector<int> (std::max((uint64_t) 1,
                                          (uint64_t) std::min(M.rows(), M.cols())));

        auto info = LAPACKE_sgetrf(LAPACK_COL_MAJOR, D.rows(), D.cols(), D.data(), D.rows(), ipiv.data());

        return LU<float> {D, ipiv, info};
    }

    template<>
    LU<double> lu(Matrix<double> &M) {
        auto D = Matrix(M);
        auto ipiv = Vector<int> (std::max((uint64_t) 1,
                                          (uint64_t) std::min(M.rows(), M.cols())));

        auto info = LAPACKE_dgetrf(LAPACK_COL_MAJOR, D.rows(), D.cols(), D.data(), D.rows(), ipiv.data());

        return LU<double> {D, ipiv, info};
    }

};

#endif //MINILA_LU_H
