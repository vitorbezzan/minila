/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_INTEGRATION_H
#define MINILA_INTEGRATION_H

#include <functional>
#include "constants.h"

namespace minila::integration {

    template<class F, typename T>
    requires std::floating_point<T>
    auto trapezium(F &function, T start, T end, uint32_t subdivisions = MINILA_TRAPEZIUM) {
        // Checks during compile time if function being used is suitable;
        // Accepts functions of one argument of same type as starting point.
        std::function<T(T)> f(function);

        auto h = (end - start) / subdivisions;
        T result = 0;
        for(uint32_t i = 0; i < subdivisions; i++)
        {
            auto a = start + h*i;
            auto b = start + h*(i + 1);
            result += (f(a) + f(b)) / 2;
        }

        return h * result;
    }

    template<class F, typename T>
    requires std::floating_point<T>
    auto simpson(F &function, T start, T end, uint32_t subdivisions = MINILA_SIMPSON) {
        // Checks during compile time if function being used is suitable;
        // Accepts functions of one argument of same type as starting point.
        std::function<T(T)> f(function);

        auto h = (end - start) / subdivisions;
        T result = 0;
        for(uint32_t i = 0; i < subdivisions; i++)
        {
            auto a = start + h*i;
            auto b = start + h*(i + 1);
            result += f(a) + 4 * f((a + b)/2) + f(b);
        }

        return (h/6) * result;
    }

    template<class F, typename T>
    requires std::floating_point<T>
    auto simpson38(F &function, T start, T end, uint32_t subdivisions = MINILA_SIMPSON_38) {
        // Checks during compile time if function being used is suitable;
        // Accepts functions of one argument of same type as starting point.
        std::function<T(T)> f(function);

        auto h = (end - start) / subdivisions;
        T result = 0;
        for(uint32_t i = 0; i < subdivisions; i++)
        {
            auto a = start + h*i;
            auto b = start + h*(i + 1);
            result += f(a) + 3*f((2*a + b)/3) + 3*f((a + 2*b)/3) + f(b);
        }

        return (h/8) * result;
    }

};

#endif //MINILA_INTEGRATION_H
