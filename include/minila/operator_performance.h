/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_OPERATOR_PERFORMANCE_H
#define MINILA_OPERATOR_PERFORMANCE_H

#include "blas_multiply.h"

namespace minila::operators::performance {

    // Vector * scalar
    Vector<float> operator*(Vector<float> &left, float right) {
        return minila::blas::multiply(left, right);
    }

    // Vector * scalar
    Vector<double> operator*(Vector<double> &left, double right) {
        return minila::blas::multiply(left, right);
    }

    // scalar * Vector
    Vector<float> operator*(float left, Vector<float> &right) {
        return minila::blas::multiply(left, right);
    }

    // scalar * Vector
    Vector<double> operator*(double left, Vector<double> &right) {
        return minila::blas::multiply(left, right);
    }

    // Vector * Vector
    float operator*(Vector<float> &left, Vector<float> &right) {
        return minila::blas::dot(left, right);
    }

    // Vector * Vector
    double operator*(Vector<double> &left, Vector<double> &right) {
        return minila::blas::dot(left, right);
    }

    // Angle between vectors
    float operator%(Vector<float> &left, Vector<float> &right) {
        float abs_l = minila::blas::dot(left, left);
        float abs_r = minila::blas::dot(right, right);

        auto cosine = minila::blas::dot(left, right) / (abs_l * abs_r);
        return std::acos(cosine);
    }

    // Angle between vectors
    double operator%(Vector<double> &left, Vector<double> &right) {
        double abs_l = minila::blas::dot(left, left);
        double abs_r = minila::blas::dot(right, right);

        auto cosine = minila::blas::dot(left, right) / (abs_l * abs_r);
        return std::acos(cosine);
    }

    // Matrix * Vector
    Vector<float> operator*(Matrix<float> &left, Vector<float> &right) {
        return minila::blas::multiply(left, right);
    }

    // Matrix * Vector
    Vector<double> operator*(Matrix<double> &left, Vector<double> &right) {
        return minila::blas::multiply(left, right);
    }

    // Vector * Matrix
    Vector<float> operator*(Vector<float> &left, Matrix<float> &right) {
        return minila::blas::multiply(left, right);
    }

    // Vector * Matrix
    Vector<double> operator*(Vector<double> &left, Matrix<double> &right) {
        return minila::blas::multiply(left, right);
    }

    // Matrix * Matrix
    Matrix<float> operator*(Matrix<float> &left, Matrix<float> &right) {
        return minila::blas::multiply(left, right);
    }

    // Matrix * Matrix
    Matrix<double> operator*(Matrix<double> &left, Matrix<double> &right) {
        return minila::blas::multiply(left, right);
    }

};

#endif //MINILA_OPERATOR_PERFORMANCE_H
