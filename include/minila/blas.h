/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#ifndef MINILA_MATRIX_MULTIPLY_H
#define MINILA_MATRIX_MULTIPLY_H

#include <cblas.h>
#include "matrix.h"
#include "vector.h"

namespace minila::blas {

    template<typename T>
    Vector<T> multiply(Vector<T> &left, T right) {
        throw std::runtime_error("Unsupported type for blas::multiply.");
    }

    template<>
    Vector<float> multiply(Vector<float> &left, float right) {
        auto result = Vector<float> (left);
        cblas_sscal(result.dimensions(), right, result.data(), 1);

        return result;
    }

    template<>
    Vector<double> multiply(Vector<double> &left, double right) {
        auto result = Vector<double> (left);
        cblas_dscal(result.dimensions(), right, result.data(), 1);

        return result;
    }

    template<typename T>
    Vector<T> multiply(T left, Vector<T> &right) {
        throw std::runtime_error("Unsupported type for blas::multiply.");
    }

    template<>
    Vector<float> multiply(float left, Vector<float> &right) {
        auto result = Vector<float> (right);
        cblas_sscal(result.dimensions(), left, result.data(), 1);

        return result;
    }

    template<>
    Vector<double> multiply(double left, Vector<double> &right) {
        auto result = Vector<double> (right);
        cblas_dscal(result.dimensions(), left, result.data(), 1);

        return result;
    }

    template<typename T>
    T dot(Vector<T> &left, Vector<T> &right) {
        throw std::runtime_error("Unsupported type for blas::dot.");
    }

    template<>
    float dot(Vector<float> &left, Vector<float> &right) {
        if(left.dimensions() != right.dimensions())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        return cblas_sdot(left.dimensions(), left.data(), 1, right.data(), 1);
    }

    template<>
    double dot(Vector<double> &left, Vector<double> &right) {
        if(left.dimensions() != right.dimensions())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        return cblas_ddot(left.dimensions(), left.data(), 1, right.data(), 1);
    }

    template<typename T>
    Vector<T> multiply(Matrix <T> &left, Vector<T> & right) {
        throw std::runtime_error("Unsupported type for blas::multiply.");
    }

    template<>
    Vector<float> multiply<float>(Matrix <float> &left, Vector<float> & right) {
        if (left.cols() != right.dimensions())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        auto result = Vector<float>(left.rows()); // Initializes with zeros.
        cblas_sgemv(CblasRowMajor, CblasNoTrans, left.rows(), left.cols(), 1.0, left.data(), left.rows(), right.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    template<>
    Vector<double> multiply<double>(Matrix <double> &left, Vector<double> & right) {
        if (left.cols() != right.dimensions())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        auto result = Vector<double>(left.rows()); // Initializes with zeros.
        cblas_dgemv(CblasRowMajor, CblasNoTrans, left.rows(), left.cols(), 1.0, left.data(), left.rows(), right.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    template<typename T>
    Vector<T> multiply(Vector<T> &left, Matrix <T> &right) {
        throw std::runtime_error("Unsupported type for blas::multiply.");
    }

    template<>
    Vector<float> multiply<float>(Vector<float> &left, Matrix <float> &right) {
        if (left.dimensions() != right.rows())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        auto result = Vector<float>(right.cols()); // Initializes with zeros.
        cblas_sgemv(CblasRowMajor, CblasTrans, right.rows(), right.cols(), 1.0, right.data(), right.rows(), left.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

    template<>
    Vector<double> multiply<double>(Vector<double> & left, Matrix < double > &right) {
        if (left.dimensions() != right.rows())
            throw std::runtime_error("Invalid axis sizes for blas::multiply.");

        auto result = Vector<double>(right.cols()); // Initializes with zeros.
        cblas_dgemv(CblasRowMajor, CblasTrans, right.rows(), right.cols(), 1.0, right.data(), right.rows(), left.data(),
                    1, 1.0, result.data(), 1);

        return result;
    }

};

#endif //MINILA_MATRIX_MULTIPLY_H
#pragma clang diagnostic pop
