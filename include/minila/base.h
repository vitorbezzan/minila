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
#include <stdexcept>

namespace minila
{
    template<typename InternalType = float>
    requires std::floating_point<InternalType>
    class BaseArray
    {
    public:
        friend class BaseArray;

        BaseArray();
        BaseArray(BaseArray<InternalType> &right);
        BaseArray(uint8_t n_axis, uint64_t *axis_size);
        BaseArray(uint8_t n_axis, uint64_t *axis_size, InternalType *values);

        virtual ~BaseArray();

        uint8_t n_axis();
        uint64_t n_elements();

        InternalType &operator[](uint64_t n_element);
        uint64_t operator()(uint8_t axis);

        BaseArray<InternalType>& operator=(const BaseArray<InternalType>& right);
        BaseArray<InternalType> operator+(const BaseArray<InternalType>& right);
        BaseArray<InternalType> operator-(const BaseArray<InternalType>& right);


    private:
        void _build_object(uint8_t n_axis, uint64_t *axis_size, InternalType *values);
        bool _check_consistency(const BaseArray<InternalType>& right);

        uint8_t _n_axis{};
        uint64_t _n_elements{};
        uint64_t *_axis_size{};
        InternalType *_values;
    };

    template<typename InternalType>
    requires std::floating_point<InternalType>
    void BaseArray<InternalType>::_build_object(uint8_t n_axis, uint64_t *axis_size, InternalType *values)
    {
        if(n_axis > 0)
        {
            _n_axis = n_axis;
            _axis_size = new uint64_t[n_axis];

            auto N = std::accumulate(axis_size, axis_size + n_axis, 1, std::multiplies());
            _n_elements = N;

            std::copy(axis_size, axis_size + n_axis, _axis_size);

            _values = new InternalType[N];
            if(values != nullptr)
                std::copy(values, values + N, _values);
        }
        else
        {
            _n_axis = 0;
            _n_elements = 0;
            _axis_size = nullptr;
            _values = nullptr;
        }
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray()
    {
        _build_object(0, nullptr, nullptr);
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray(BaseArray<InternalType> &right)
    {
        _build_object(right._n_axis, right._axis_size, right._values);
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray(uint8_t n_axis, uint64_t *axis_size)
    {
        _build_object(n_axis, axis_size, nullptr);
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    BaseArray<InternalType>::BaseArray(uint8_t n_axis, uint64_t *axis_size, InternalType *values)
    {
        _build_object(n_axis, axis_size, values);
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
    uint8_t BaseArray<InternalType>::n_axis()
    {
        return _n_axis;
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    uint64_t BaseArray<InternalType>::n_elements()
    {
        return _n_elements;
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    InternalType &BaseArray<InternalType>::operator[](uint64_t n_element)
    {
        if(n_element >= _n_elements)
            throw std::invalid_argument("Invalid ranges for element.");

        return _values[n_element];
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    uint64_t BaseArray<InternalType>::operator()(uint8_t axis)
    {
        if(axis >= _n_axis)
            throw std::invalid_argument("Invalid ranges for axis.");

        return _axis_size[axis];
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>BaseArray<InternalType> &
    BaseArray<InternalType>::operator=(const BaseArray<InternalType> &right)
    {
        if (&right != this)
        {
            delete[] _axis_size;
            delete[] _values;

            _build_object(right._n_axis, right._axis_size, right._values);
        }
        return *this;
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>
    bool BaseArray<InternalType>::_check_consistency(const BaseArray<InternalType> &right)
    {
        if(_n_axis == right._n_axis)
            if(std::equal(_axis_size, _axis_size + _n_axis, right._axis_size))
                return true;
            else
                return false;
        else
            return false;
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>BaseArray<InternalType>
    BaseArray<InternalType>::operator+(const BaseArray<InternalType> &right)
    {
        if(_check_consistency(right))
        {
            auto new_values = new InternalType[_n_elements];
            std::transform(_values, _values + _n_elements, right._values, new_values, std::plus{});

            return BaseArray<InternalType> (_n_axis, _axis_size, new_values);
        }

        throw std::invalid_argument("Invalid axis for operation +.");
    }

    template<typename InternalType>
    requires std::floating_point<InternalType>BaseArray<InternalType>
    BaseArray<InternalType>::operator-(const BaseArray<InternalType> &right)
    {
        if(_check_consistency(right))
        {
            auto new_values = new InternalType[_n_elements];
            std::transform(_values, _values + _n_elements, right._values, new_values, std::minus{});

            return BaseArray<InternalType> (_n_axis, _axis_size, new_values);
        }

        throw std::invalid_argument("Invalid axis for operation -.");
    }

}

#endif //MINILA_BASE_H
