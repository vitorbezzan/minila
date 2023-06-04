/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_PRINT_H
#define MINILA_PRINT_H

#include <iostream>
#include "matrix.h"
#include "vector.h"

namespace minila {

    // Simple functions to print matrix and vectors
    template<typename T>
    void print(Vector<T> &v) {
        std::cout<<"[";
        for(uint64_t d = 1; d <= v.dimensions() - 1; d++)
        {
            std::cout<<v(d)<<",\t";
        }
        std::cout<<v(v.dimensions())<<"]"<<std::endl;
    }

    // Simple functions to print matrix and vectors
    template<typename T>
    void print(Matrix<T> &M) {
        std::cout<<"[";
        for(uint64_t row = 1; row <= M.rows(); row++)
        {
            std::cout<<"[";
            for(uint64_t col = 1; col <= M.cols() - 1; col++)
                std::cout<<M(row, col)<<",\t";
            std::cout<<M(row, M.cols())<<"]";

            std::cout<<"]"<<std::endl;
        }
    }

};

#endif //MINILA_PRINT_H
