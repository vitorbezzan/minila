/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_BROWNIAN_H
#define MINILA_BROWNIAN_H

#include <memory>
#include "base.h"

namespace minila::process {

    template<typename T>
    class Brownian : public Process<T> {
        // Implements basic Brownian motion
    public:
        Brownian(T initial, Process<T>* mean, Process<T>* sigma): _initial(initial), _mean(mean), _sigma(sigma){};
        std::unique_ptr<T*> path(uint64_t steps, uint64_t seed) override;

    private:
        T _initial;
        Process<T>* _mean;
        Process<T>* _sigma;
    };

    template<typename T>
    std::unique_ptr<T*> Brownian<T>::path(uint64_t steps, uint64_t seed) {
        // All generate pointers
        auto dB = this->generate_normal(steps, seed);
        auto mean = _mean->path(steps, seed + 1);
        auto sigma = _sigma->path(steps, seed + 2);

        auto p = std::make_unique<T*>(new T[steps]);

        (*p)[0] = _initial;
        for(uint64_t i = 1; i < steps; i++)
        {
            (*p)[i] = (*p)[i-1] + (*mean)[i] + (*dB)[i] * (*sigma)[i];
        }

        return p;
    }

};


#endif //MINILA_BROWNIAN_H
