/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_GEOMETRIC_H
#define MINILA_GEOMETRIC_H

#include <cmath>
#include "base.h"

namespace minila::process {

    template<typename T>
    class Geometric : public Process<T> {
        // Implements basic Geometric Brownian Motion
    public:
        Geometric(T initial, Process<T>* mean, Process<T>* sigma): _initial(initial), _mean(mean), _sigma(sigma) {};
        std::unique_ptr<T*> path(uint64_t steps, uint64_t seed) override;

    private:
        T _initial;
        Process<T>* _mean;
        Process<T>* _sigma;
    };

    template<typename T>
    std::unique_ptr<T*> Geometric<T>::path(uint64_t steps, uint64_t seed) {
        // All generate pointers
        auto dB = this->generate_normal(steps, seed);
        auto mean = _mean->path(steps, seed + 1);
        auto sigma = _sigma->path(steps, seed + 2);

        auto p = std::make_unique<T*>(new T[steps]);

        (*p)[0] = _initial;
        for(uint64_t i = 1; i < steps; i++)
        {
            auto m = (*mean)[i] * (*p)[i-1];
            auto v = (*sigma)[i] * (*p)[i-1];
            auto c = 0.5 * (std::pow((*sigma)[i], 2) * (*p)[i-1]);

            (*p)[i] = (*p)[i-1] + m + (v * (*dB)[i]) + c * ((std::pow((*dB)[i], 2)) - 1);
        }

        return p;
    }

};

#endif //MINILA_GEOMETRIC_H
