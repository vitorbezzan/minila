/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_OPERATOR_NAIVE_H
#define MINILA_OPERATOR_NAIVE_H

#include "naive.h"

namespace minila::operators::naive {

    // Vector * scalar
    template<typename T1, typename T2>
    auto operator*(Vector<T1> &left, T2 right) {
        return minila::naive::multiply(left, right);
    }

    // scalar * Vector
    template<typename T1, typename T2>
    auto operator*(T2 left, Vector<T1> &right) {
        return minila::naive::multiply(left, right);
    }

    // Vector * Vector
    template<typename T1, typename T2>
    auto operator*(Vector<T1> &left, Vector<T2> &right) {
        return minila::naive::dot(left, right);
    }

    // Angle between vectors
    template<typename T1, typename T2>
    auto operator%(Vector<T1> &left, Vector<T2> &right) {
        return minila::naive::angle(left, right);
    }

    // Matrix * Vector
    template<typename T1, typename T2>
    auto operator*(Matrix<T1> &left, Vector<T2> &right) {
        return minila::naive::multiply(left, right);
    }

    // Vector * Matrix
    template<typename T1, typename T2>
    auto operator*(Vector<T1> &left, Matrix<T2> &right) {
        return minila::naive::multiply(left, right);
    }

    // Matrix * Matrix
    template<typename T1, typename T2>
    auto operator*(Matrix<T1> &left, Matrix<T2> &right) {
        return minila::naive::multiply(left, right);
    }

};

#endif //MINILA_OPERATOR_NAIVE_H
