/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_NAIVE_H
#define MINILA_NAIVE_H

#include <cmath>
#include <numeric>
#include <stdexcept>
#include "matrix.h"
#include "vector.h"

namespace minila::naive {

    // Vector * scalar
    template<typename T1, typename T2>
    inline auto multiply(Vector<T1> &left, T2 right) {
        using R = decltype(T1(0) + T2(0));
        auto result = Vector<R> (left.dimensions());

        std::transform(left.data(), left.data() + left.dimensions(), result.data(),
                       [&right](double element) {return element *= right;});

        return result;
    }

    // scalar * Vector
    template<typename T1, typename T2>
    inline auto multiply(T2 left, Vector<T1> &right) {
        using R = decltype(T1(0) + T2(0));
        auto result = Vector<R> (right.dimensions());

        std::transform(right.data(), right.data() + right.dimensions(), result.data(),
                       [&left](double element) {return element *= left;});

        return result;
    }

    // Vector * Vector
    template<typename T1, typename T2>
    inline auto dot(Vector<T1> &left, Vector<T2> &right)
    {
        if(left.dimensions() != right.dimensions())
            throw std::invalid_argument("Invalid axis sizes on operation dot.");

        using R = decltype(T1(0) * T2(0));
        R result = std::inner_product(left.data(), left.data() + left.dimensions(), right.data(), 0);

        return result;
    }

    // Matrix * Vector
    template<typename T1, typename T2>
    auto multiply(Matrix<T1> &M, Vector<T2> &v) {
        if(M.cols() != v.dimensions())
            throw std::invalid_argument("Invalid axis sizes on operation naive::multiply.");

        using R = decltype(T1(0) * T2(0));
        Vector<R> result(M.rows());

        for (uint64_t i = 1; i <= result.dimensions(); i++)
            for (uint64_t k = 1; k <= M.cols(); k++)
                result(i) += M(i, k) * v(k);

        return result;
    }

    // Vector * Matrix
    template<typename T1, typename T2>
    auto multiply(Vector<T1> &v, Matrix<T2> &M) {
        if (v.dimensions() != M.rows())
            throw std::invalid_argument("Invalid axis sizes on operation naive::multiply.");

        using R = decltype(T1(0) * T2(0));
        Vector<R> result(M.cols());

        for(uint64_t i = 1; i <= result.dimensions(); i++)
            for (uint64_t k = 1; k <= M.cols(); k++)
                result(i) += v(k) * M(k, i);

        return result;
    }

    // Matrix * Matrix
    template<typename T1, typename T2>
    auto multiply(Matrix<T1> &left, Matrix<T2> &right) {
        if (left.cols() != right.rows())
            throw std::invalid_argument("Invalid axis sizes on operation naive::multiply.");

        using R = decltype(T1(0) * T2(0));
        Matrix<R> result(left.rows(), right.cols());

        for (uint64_t i = 1; i <= result.rows(); i++)
            for (uint64_t k = 1; k <= left.cols(); k++)
                for (uint64_t j = 1; j <= result.cols(); j++)
                    result(i, j) += left(i, k) * right(k, j);

        return result;
    }

    // Absolute value of vector
    template<typename T>
    inline auto abs(Vector<T> &left)
    {
        return dot(left, left);
    }

    // Cosine of angle between Vector
    template<typename T1, typename T2>
    inline auto cosine(Vector<T1> &left, Vector<T2> &right)
    {
        return dot(left, right) / (abs(left) * abs(right));
    }

    // Angle between vectors
    template<typename T1, typename T2>
    inline auto angle(Vector<T1> &left, Vector<T2> &right)
    {
        return std::acos(cosine(left, right));
    }

};

#endif //MINILA_NAIVE_H
