/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_MATRIX_H
#define MINILA_MATRIX_H

#include "base.h"

namespace minila
{
    bool MINILA_ROW_MAJOR = true;

    template<typename InternalType>
    class Matrix: private BaseArray<InternalType>
    {
    public:
        uint64_t rows();
        uint64_t cols();

    private:
        uint64_t _rows;
        uint64_t _cols;
    };

    template<typename InternalType>
    uint64_t Matrix<InternalType>::rows()
    {
        return _rows;
    }

    template<typename InternalType>
    uint64_t Matrix<InternalType>::cols()
    {
        return _cols;
    }

};

#endif //MINILA_MATRIX_H
