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

namespace minila {

    template<typename T> requires std::is_arithmetic_v<T>
    class BaseArray {
    public:

        friend class BaseArray;

        // Constructors and destructors
        // Base constructor
        BaseArray() : _data(nullptr), _dimensions(nullptr), _ndim(0), _n_elements(0) {};

        // Copy constructor for BaseArray
        BaseArray(const BaseArray<T> &right);

        // Creates empty BaseArray
        template<size_t N>
        explicit BaseArray(const uint64_t (&dimensions)[N]);

        // Creates BaseArray with values
        template<size_t N1, size_t N2>
        BaseArray(const uint64_t (&dimensions)[N1], const T (&values)[N2]);

        // Virtual destructor
        virtual ~BaseArray();

        // Setter and getters
        // Gets dimensions
        uint64_t ndim();

        // Gets element from BaseArray
        template<size_t N>
        T &operator()(const uint64_t (&index)[N]);

        // Gets number of elements in dimension
        uint64_t operator[](uint64_t dimension);

        // Operators
        BaseArray<T> &operator=(const BaseArray<T> &right);

        BaseArray<T> operator+(const BaseArray<T> &right);

        BaseArray<T> operator-(const BaseArray<T> &right);

        // Returns pointer to data
        T *data();

    private:
        T *_data;
        uint64_t *_dimensions;

        // Tracking the size of multidimensional array.
        uint64_t _ndim;
        uint64_t _n_elements;

        bool _check_dimensions(const BaseArray<T> &right);
    };

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T>::BaseArray(const BaseArray<T> &right) : BaseArray() {
        _ndim = right._ndim;
        _n_elements = right._n_elements;

        if (right._ndim > 0) {
            _dimensions = new uint64_t[right._ndim];
            std::copy(right._dimensions, right._dimensions + right._ndim, _dimensions);

            _data = new T[right._n_elements];
            std::copy(right._data, right._data + right._n_elements, _data);
        }
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    template<size_t N>
    BaseArray<T>::BaseArray(const uint64_t (&dimensions)[N]) : BaseArray() {
        _ndim = uint64_t(N);

        if (N > 0) {
            _n_elements = std::accumulate(
                    std::begin(dimensions),
                    std::end(dimensions),
                    1,
                    std::multiplies<T>()
            );

            _dimensions = new uint64_t[N];
            std::copy(std::begin(dimensions), std::end(dimensions), _dimensions);

            _data = new T[_n_elements];
        }
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    template<size_t N1, size_t N2>
    BaseArray<T>::BaseArray(const uint64_t (&dimensions)[N1], const T (&values)[N2]) : BaseArray(dimensions) {
        if (_n_elements == N2) {
            std::copy(std::begin(values), std::end(values), _data);
        }

        throw std::invalid_argument("Dimension size mismatch for operation.");
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T>::~BaseArray() {
        delete[] _data;
        delete[] _dimensions;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    uint64_t BaseArray<T>::ndim() {
        return this->_ndim;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    template<size_t N>
    T &BaseArray<T>::operator()(const uint64_t (&index)[N]) {
        if (_ndim == N) {
            uint64_t _index = 0;
            for (uint64_t i = 0; i < N; i++) {
                if (index[i] >= _dimensions[i])
                    throw std::invalid_argument("Axis size mismatch for operation.");

                uint64_t _product = 1;
                for (uint64_t j = i + 1; j < N; j++) {
                    _product *= _dimensions[j];
                }
                _index += index[i] * _product;
            }

            return _data[_index];
        }

        throw std::invalid_argument("Index size mismatch for operation.");
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    uint64_t BaseArray<T>::operator[](uint64_t dimension) {
        return _dimensions[dimension];
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> &BaseArray<T>::operator=(const BaseArray<T> &right) {
        if (&right != this) {
            auto new_dim = new uint64_t[right._ndim];
            std::copy(right._dimensions, right._dimensions + right._ndim, new_dim);
            _dimensions = new_dim;
            _ndim = right._ndim;

            auto new_data = new T[right._n_elements];
            std::copy(right._data, right._data + right._n_elements, new_data);
            _data = new_data;
            _n_elements = right._n_elements;
        }

        return *this;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> BaseArray<T>::operator+(const BaseArray<T> &right) {
        if (_check_dimensions(right)) {
            std::transform(
                    _data,
                    _data + _n_elements,
                    right._data,
                    _data,
                    std::plus<T>());
        }

        throw std::invalid_argument("Dimension size mismatch for operation.");
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    BaseArray<T> BaseArray<T>::operator-(const BaseArray<T> &right) {
        if (_check_dimensions(right)) {
            std::transform(
                    _data,
                    _data + _n_elements,
                    right._data,
                    _data,
                    std::minus<T>());
        }

        throw std::invalid_argument("Dimension size mismatch for operation.");
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    T *BaseArray<T>::data() {
        return _data;
    }

    template<typename T>
    requires std::is_arithmetic_v<T>
    inline bool BaseArray<T>::_check_dimensions(const BaseArray<T> &right) {
        if (_ndim != right._ndim)
            return false;

        return std::equal(_dimensions, _dimensions + _ndim, right._dimensions);
    }

};

#endif //MINILA_BASE_H
