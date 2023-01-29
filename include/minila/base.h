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

    template<typename Type> requires std::floating_point<Type>
    class BaseArray {
    public:

        friend class BaseArray;

        BaseArray() : _values({}), _dimensions({}) {};
        BaseArray(const BaseArray<Type> &right);
        BaseArray(const std::vector<uint64_t> &dimensions, const std::vector<Type> &values);
        explicit BaseArray(const std::vector<uint64_t> &dimensions);
        virtual ~BaseArray() = default;

        BaseArray<Type> &operator=(const BaseArray<Type> &right);
        BaseArray<Type> operator+(const BaseArray<Type> &right);
        BaseArray<Type> operator-(const BaseArray<Type> &right);

        Type &operator()(const std::vector<uint64_t> &index);
        uint64_t operator[](uint64_t dimension);

        template<typename External>
        BaseArray<External> cast();

        Type *data();

    private:
        void _check_dimensions(const BaseArray<Type> &right);

        std::vector<Type> _values;
        std::vector<uint64_t> _dimensions;
    };

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type>::BaseArray(const BaseArray<Type> &right) {
        _dimensions = std::vector<uint64_t>(right._dimensions);
        _values = std::vector<Type>(right._values);
    }

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type>::BaseArray(const std::vector<uint64_t> &dimensions) {
        auto N = std::accumulate(dimensions.begin(), dimensions.end(), 1, std::multiplies<Type>());

        _dimensions = std::vector<uint64_t>(dimensions);
        _values = std::vector<Type>(N, 0.0);
    }

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type>::BaseArray(const std::vector<uint64_t> &dimensions, const std::vector<Type> &values) {
        _dimensions = std::vector<uint64_t>(dimensions);
        _values = std::vector<Type>(values);
    }

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type> &BaseArray<Type>::operator=(const BaseArray<Type> &right) {
        _dimensions = std::vector<uint64_t>(right._dimensions);
        _values = std::vector<Type>(right._values);

        return *this;
    }

    template<typename Type>
    requires std::floating_point<Type>
    void BaseArray<Type>::_check_dimensions(const BaseArray<Type> &right) {
        if (_dimensions != right._dimensions)
            throw std::invalid_argument("Dimensions mismatch for operation.");
    }

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type> BaseArray<Type>::operator+(const BaseArray<Type> &right) {
        _check_dimensions(right);
        auto values = std::vector<Type>(right._values);
        std::transform(
                _values.begin(),
                _values.end(),
                values.begin(),
                values.begin(),
                std::plus<Type>());

        return BaseArray<Type>(_dimensions, values);
    }

    template<typename Type>
    requires std::floating_point<Type>
    BaseArray<Type> BaseArray<Type>::operator-(const BaseArray<Type> &right) {
        _check_dimensions(right);
        auto values = std::vector<Type>(right._values);
        std::transform(
                _values.begin(),
                _values.end(),
                values.begin(),
                values.begin(),
                std::minus<Type>());

        return BaseArray<Type>(_dimensions, values);
    }

    // All indexes are stored as row major
    template<typename Type>
    requires std::floating_point<Type>
    Type &BaseArray<Type>::operator()(const std::vector<uint64_t> &index) {
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

    template<typename Type>
    requires std::floating_point<Type>
    uint64_t BaseArray<Type>::operator[](uint64_t dimension) {
        return _dimensions[dimension];
    }

    template<typename Type>
    requires std::floating_point<Type>
    template<typename External>
    BaseArray<External> BaseArray<Type>::cast() {
        return BaseArray<External>(_dimensions, std::vector<External>(_values.begin(), _values.end()));
    }

    template<typename Type>
    requires std::floating_point<Type>Type *BaseArray<Type>::data() {
        return _values.data();
    }

}

#endif //MINILA_BASE_H
