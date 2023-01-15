/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_BASE_H
#define MINILA_BASE_H

#include <algorithm>
#include <concepts>
#include <numeric>

namespace minila
{
    template<typename InternalType = float>
    requires std::floating_point<InternalType>
    class BaseArray
    {
    public:

        // Constructor/destructor for BaseArray
        BaseArray(uint8_t n_axis, uint64_t *axis_size);
        BaseArray(uint8_t n_axis, uint64_t *axis_size, InternalType *values);
        virtual ~BaseArray();

        // Some useful functions
        uint8_t n_axis() {return _n_axis;}
        uint64_t n_elements() {return _n_elements;}

        // Manipulate data within structure
        InternalType &operator[](uint64_t n_element);
        InternalType &operator[](uint64_t &n_element);

        // Get axis size
        uint64_t operator()(uint8_t axis);
        uint64_t operator()(uint8_t &axis);

        // Other operators

    private:
        uint8_t _n_axis;  // Number of dimensions.
        uint64_t _n_elements;  // Number of elements in array.
        InternalType *_values; // Linear array to store values.
        uint64_t *_axis_size;  // Size of each axis.
    };

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray(uint8_t n_axis, uint64_t *axis_size)
    {
        auto N = std::accumulate(axis_size, axis_size + n_axis, 1, std::multiplies());

        _n_axis = n_axis;
        _n_elements = N;
        _values = new InternalType[_n_elements];

        _axis_size = new uint64_t[n_axis];
        std::copy(axis_size, axis_size + n_axis, _axis_size);
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray(uint8_t n_axis, uint64_t *axis_size, InternalType *values)
    {
        auto N = std::accumulate(axis_size, axis_size + n_axis, 1, std::multiplies());

        _n_axis = n_axis;
        _n_elements = N;

        _values = new InternalType[_n_elements];
        std::copy(values, values + N, _values);

        _axis_size = new uint64_t[n_axis];
        std::copy(axis_size, axis_size + n_axis, _axis_size);
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::~BaseArray()
    {
        delete[] _values;
        delete[] _axis_size;
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    InternalType &BaseArray<InternalType>::operator[](uint64_t n_element)
    {
        assert(n_element >= 0);
        assert(n_element < _n_elements);
        return _values[n_element];
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    InternalType &BaseArray<InternalType>::operator[](uint64_t &n_element)
    {
        assert(n_element >= 0);
        assert(n_element < _n_elements);
        return _values[n_element];
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    uint64_t BaseArray<InternalType>::operator()(uint8_t axis)
    {
        assert(axis >= 0);
        assert(axis < _n_axis);
        return _axis_size[axis];
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    uint64_t BaseArray<InternalType>::operator()(uint8_t &axis)
    {
        assert(axis >= 0);
        assert(axis < _n_axis);
        return _axis_size[axis];
    }

}

#endif //MINILA_BASE_H
