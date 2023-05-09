/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_SVD_H
#define MINILA_SVD_H

#include <stdexcept>
#include <lapacke.h>
#include "constants.h"
#include "matrix.h"

namespace minila {

    template<typename T>
    struct SVD {
        Matrix<T> U; // MxM left singular matrix
        Vector<T> s; // min(M,N) singular values
        Matrix<T> V; // NxN right singular matrix

        int info = 0; // Return code for SVD function
    };

    template<typename T>
    SVD<T> svd(Matrix<T> &M) {
        throw std::runtime_error("Unsupported type for SVD.");
    }

    template<>
    SVD<float> svd(Matrix<float> &M) {
        Matrix<float> U(M.rows(), M.rows());
        Matrix<float> V(M.cols(), M.cols());
        Vector<float> s(std::min(M.rows(), M.cols()));
        
        //To be unmercifully destroyed.
        Matrix<float> _temp(M);
        
        // To be used by the C-interface, meh.
        Vector<float> b(std::min(M.rows(), M.cols()));

        auto info = LAPACKE_sgesvd(LAPACK_COL_MAJOR, 'A', 'A', M.rows(), M.cols(), _temp.data(),
                                   M.rows(), s.data(), U.data(), U.rows(), V.data(), V.rows(), b.data());
        
        return SVD<float> {U, s, V, info};
    }

    template<>
    SVD<double> svd(Matrix<double> &M) {
        Matrix<double> U(M.rows(), M.rows());
        Matrix<double> V(M.cols(), M.cols());
        Vector<double> s(std::min(M.rows(), M.cols()));

        //To be unmercifully destroyed.
        Matrix<double> _temp(M);

        // To be used by the C-interface, meh.
        Vector<double> b(std::min(M.rows(), M.cols()));

        auto info = LAPACKE_dgesvd(LAPACK_COL_MAJOR, 'A', 'A', M.rows(), M.cols(), _temp.data(),
                                   M.rows(), s.data(), U.data(), U.rows(), V.data(), V.rows(), b.data());

        return SVD<double> {U, s, V, info};
    }

    template<typename T>
    inline uint64_t rank(SVD<T> &S) {
        uint64_t r = 0;
        for(auto i = 1; i <= S.s.dimensions(); i++)
            if(std::fabs(S.s(i)) >= MINILA_SVD_RANK)
                r++;

        return r;
    }
};

#endif //MINILA_SVD_H
