/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_NUMERICAL_H
#define MINILA_NUMERICAL_H

#include <cmath>
#include <functional>
#include "constants.h"

namespace minila::numerical {

    struct RealRoot {
        uint8_t status;
        double_t root;
        uint16_t iter;
        double_t dx_precision;
        double_t rt_precision;
    };

    template<class F, typename T1>
    requires std::floating_point<T1>
    inline auto derivative(F &f, T1 x, uint8_t order = MINILA_DX_ORDER, double_t dx = MINILA_DX_PRECISION) {
        if (order == 2)
            return (f(x + dx) - f(x - dx)) / (2 * dx);

        return (-f(x + 2 * dx) + 8 * f(x + dx) - 8 * f(x - dx) + f(x - 2 * dx)) / (12 * dx);
    }

    template<class F, typename T>
    requires std::floating_point<T>
    auto newton(F &function, T starting, uint16_t iterations = MINILA_MAXITER) {
        // Checks during compile time if function being used is suitable;
        // Accepts functions of one argument of same type as starting point.
        std::function<T(T)> f(function);

        // Accepts several input types, but always coerce them to double
        // for maximum precision.
        uint16_t n = 1;
        uint8_t status = -1;

        double x0 = starting;
        double xn = starting;

        while (n < iterations) {
            xn = x0 - f(x0) / derivative(f, x0);
            if (std::fabs(xn - x0) <= MINILA_RT_PRECISION) {
                status = 0;
                break;
            }

            x0 = xn;
            n++;
        }

        return RealRoot{status, xn, n, MINILA_DX_PRECISION, MINILA_RT_PRECISION};
    }

    template<class F, class D, typename T>
    requires std::floating_point<T>
    auto newton(F &function, D &_derivative, T starting, uint16_t iterations = MINILA_MAXITER) {
        // Checks during compile time if function being used is suitable;
        // Accepts functions of one argument of same type as starting point.
        std::function<T(T)> f(function);
        std::function<T(T)> d(_derivative);

        // Accepts several input types, but always coerce them to double
        // for maximum precision.
        uint16_t n = 1;
        uint8_t status = -1;

        double x0 = starting;
        double xn = starting;

        while (n < iterations) {
            xn = x0 - f(x0) / d(f, x0);
            if (std::fabs(xn - x0) <= MINILA_RT_PRECISION) {
                status = 0;
                break;
            }

            x0 = xn;
            n++;
        }

        return RealRoot{status, xn, n, MINILA_DX_PRECISION, MINILA_RT_PRECISION};
    }

};

#endif //MINILA_NUMERICAL_H
