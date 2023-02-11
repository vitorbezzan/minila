/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_OPERATORS_H
#define MINILA_OPERATORS_H

#include <cmath>
#include "blas.h"
#include "matrix.h"
#include "vector.h"

namespace minila::op {

    namespace naive {

        template<typename T1, typename T2>
        auto operator*(Vector<T1> &left, T2 right) {
            return minila::naive::multiply(left, right);
        }

        template<typename T1, typename T2>
        auto operator*(T2 left, Vector<T1> &right) {
            return minila::naive::multiply(left, right);
        }

        template<typename T1, typename T2>
        auto operator*(Vector<T1> &left, Vector<T2> &right) {
            return minila::naive::dot(left, right);
        }

        template<typename T1, typename T2>
        auto operator%(Vector<T1> &left, Vector<T2> &right) {
            return minila::naive::angle(left, right);
        }

        template<typename T1, typename T2>
        auto operator*(Matrix<T1> &left, Vector<T2> &right) {
            return minila::naive::multiply(left, right);
        }

        template<typename T1, typename T2>
        auto operator*(Vector<T1> &left, Matrix<T2> &right) {
            return minila::naive::multiply(left, right);
        }

        template<typename T1, typename T2>
        auto operator*(Matrix<T1> &left, Matrix<T2> &right) {
            return minila::naive::multiply(left, right);
        }

    };

    namespace performance {

        Vector<float> operator*(Vector<float> &left, float right) {
            return minila::blas::multiply(left, right);
        }

        Vector<double> operator*(Vector<double> &left, double right) {
            return minila::blas::multiply(left, right);
        }

        Vector<float> operator*(float left, Vector<float> &right) {
            return minila::blas::multiply(left, right);
        }

        Vector<double> operator*(double left, Vector<double> &right) {
            return minila::blas::multiply(left, right);
        }

        float operator*(Vector<float> &left, Vector<float> &right) {
            return minila::blas::dot(left, right);
        }

        double operator*(Vector<double> &left, Vector<double> &right) {
            return minila::blas::dot(left, right);
        }

        float operator%(Vector<float> &left, Vector<float> &right) {
            float abs_l = minila::blas::dot(left, left);
            float abs_r = minila::blas::dot(right, right);

            auto cosine = minila::blas::dot(left, right) / (abs_l * abs_r);
            return std::acos(cosine);
        }

        double operator%(Vector<double> &left, Vector<double> &right) {
            double abs_l = minila::blas::dot(left, left);
            double abs_r = minila::blas::dot(right, right);

            auto cosine = minila::blas::dot(left, right) / (abs_l * abs_r);
            return std::acos(cosine);
        }

        Vector<float> operator*(Matrix<float> &left, Vector<float> &right) {
            return minila::blas::multiply(left, right);
        }

        Vector<double> operator*(Matrix<double> &left, Vector<double> &right) {
            return minila::blas::multiply(left, right);
        }

        Vector<float> operator*(Vector<float> &left, Matrix<float> &right) {
            return minila::blas::multiply(left, right);
        }

        Vector<double> operator*(Vector<double> &left, Matrix<double> &right) {
            return minila::blas::multiply(left, right);
        }

        Matrix<float> operator*(Matrix<float> &left, Matrix<float> &right) {
            return minila::blas::multiply(left, right);
        }

        Matrix<double> operator*(Matrix<double> &left, Matrix<double> &right) {
            return minila::blas::multiply(left, right);
        }

    };
};

#endif //MINILA_OPERATORS_H
