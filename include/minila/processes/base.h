/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_PROCESS_BASE_H
#define MINILA_PROCESS_BASE_H

#include <memory>
#include <random>
#include "../base.h"

namespace minila::process {

    template<typename T>
    class Process {
        // Implements base Process, and also implements constant processes.
        // Also implements random number generation.
    public:
        Process(): _initial(0) {}; // Default constructor
        explicit Process(T initial): _initial(initial) {};
        T initial() {return this->_initial;};

        virtual std::unique_ptr<T*> path(uint64_t steps, uint64_t seed);
        std::unique_ptr<T*> generate_normal(uint64_t steps, uint64_t seed);  // Generates normal numbers

    private:
        T _initial;
    };

    template<typename T>
    std::unique_ptr<T*> Process<T>::path(uint64_t steps, uint64_t seed) {
        // This function returns a unique_ptr containing actual path.
        // This is used to keep everything memory-safe, no dangling pointers
        auto path = std::make_unique<T*>(new T[steps]);
        std::fill(*path, *path + steps, _initial);

        return path;
    }

    template<typename T>
    std::unique_ptr<T*> Process<T>::generate_normal(uint64_t steps, uint64_t seed) {
        // Same thing as above
        auto g = std::mt19937_64(seed);
        auto d = std::normal_distribution<T>(0.0, 1.0);

        auto sequence = std::make_unique<T*>(new T[steps]);
        std::generate(*sequence, *sequence + steps, [&](){return d(g);});

        return sequence;
    }

};

#endif //MINILA_PROCESS_BASE_H
