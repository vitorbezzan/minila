/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_BASE_H
#define MINILA_BASE_H

#include <functional>
#include <numeric>
#include <stdexcept>
#include <vector>

namespace minila {

    template<typename T> requires std::is_arithmetic_v<T>
    class BaseArray {
    public:

        friend class BaseArray;

        BaseArray() : _values({}), _dimensions({}) {};
        BaseArray(const BaseArray<T> &right);
        BaseArray(const std::vector<uint64_t> &dimensions, const std::vector<T> &values);
        explicit BaseArray(const std::vector<uint64_t> &dimensions);
        virtual ~BaseArray() = default;

        BaseArray<T> &operator=(const BaseArray<T> &right);
        BaseArray<T> operator+(const BaseArray<T> &right);
        BaseArray<T> operator-(const BaseArray<T> &right);

        T &operator()(const std::vector<uint64_t> &index);
        uint64_t operator[](uint64_t dimension);

        T *data();

    private:
        void _check_dimensions(const BaseArray<T> &right);

        std::vector<T> _values;
        std::vector<uint64_t> _dimensions;
    };

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T>::BaseArray(const BaseArray<T> &right) {
        _dimensions = std::vector<uint64_t>(right._dimensions);
        _values = std::vector<T>(right._values);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T>::BaseArray(const std::vector<uint64_t> &dimensions) {
        auto N = std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<T>());

        _dimensions = std::vector<uint64_t>(dimensions);
        _values = std::vector<T>(N, 0.0);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T>::BaseArray(const std::vector<uint64_t> &dimensions, const std::vector<T> &values) {
        _dimensions = std::vector<uint64_t>(dimensions);
        _values = std::vector<T>(values);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> &BaseArray<T>::operator=(const BaseArray<T> &right) {
        _dimensions = std::vector<uint64_t>(right._dimensions);
        _values = std::vector<T>(right._values);

        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    void BaseArray<T>::_check_dimensions(const BaseArray<T> &right) {
        if (_dimensions != right._dimensions)
            throw std::invalid_argument("Dimensions mismatch for operation.");
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> BaseArray<T>::operator+(const BaseArray<T> &right) {
        _check_dimensions(right);
        auto values = std::vector<T>(right._values);
        std::transform(
                _values.begin(),
                _values.end(),
                values.begin(),
                values.begin(),
                std::plus<T>());

        return BaseArray<T>(_dimensions, values);
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> BaseArray<T>::operator-(const BaseArray<T> &right) {
        _check_dimensions(right);
        auto values = std::vector<T>(right._values);
        std::transform(
                _values.begin(),
                _values.end(),
                values.begin(),
                values.begin(),
                std::minus<T>());

        return BaseArray<T>(_dimensions, values);
    }

    // All indexes are stored as row major
    template<typename T>
    requires std::is_arithmetic_v<T>
    T &BaseArray<T>::operator()(const std::vector<uint64_t> &index) {
        if (_dimensions.size() != index.size())
            throw std::invalid_argument("Index size mismatch for operation.");

        uint64_t _index = 0;
        for (uint64_t i = 0; i < index.size(); i++) {
            if (index[i] >= _dimensions[i])
                throw std::invalid_argument("Axis size mismatch for operation.");

            uint64_t _product = 1;
            for (uint64_t j = i + 1; j < index.size(); j++) {
                _product *= _dimensions[j];
            }
            _index += index[i] * _product;
        }

        return _values[_index];
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    uint64_t BaseArray<T>::operator[](uint64_t dimension) {
        return _dimensions[dimension];
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    T *BaseArray<T>::data() {
        return _values.data();
    }

}

#endif //MINILA_BASE_H
