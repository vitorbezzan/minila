/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_VECTOR_H
#define MINILA_VECTOR_H

#include "base.h"

namespace minila {

    template<typename T>
    class Vector {

    public:
        friend class Vector;

        Vector() : _data(BaseArray <T> ()), _dimensions(0) {}
        Vector(const Vector<T> &right);
        explicit Vector(BaseArray <T> &right);
        explicit Vector(uint64_t dimensions);

        T &operator()(uint64_t dimension);
        Vector<T> operator+(const Vector<T> &right);
        Vector<T> operator-(const Vector<T> &right);

        uint64_t dimensions();
        T *data();

    private:
        BaseArray <T> _data;
        uint64_t _dimensions;
    };

    template<typename T>
    Vector<T>::Vector(const Vector<T> &right) {
        _dimensions = right._dimensions;
        _data = right._data;
    }

    template<typename T>
    Vector<T>::Vector(BaseArray<T> &right) {
        _dimensions = right[0];
        _data = right;
    }

    template<typename T>
    Vector<T>::Vector(uint64_t dimensions) {
        _dimensions = dimensions;
        _data = BaseArray < T > ({ dimensions, });
    }

    template<typename T>
    T &Vector<T>::operator()(uint64_t dimension) {
        return _data({dimension - 1,});
    }

    template<typename T>
    Vector<T> Vector<T>::operator+(const Vector<T> &right) {
        auto result = _data + right._data;
        return Vector<T>(result);
    }

    template<typename T>
    Vector<T> Vector<T>::operator-(const Vector<T> &right) {
        auto result = _data - right._data;
        return Vector<T>(result);
    }

    template<typename T>
    uint64_t Vector<T>::dimensions() {
        return _dimensions;
    }

    template<typename T>
    T *Vector<T>::data() {
        return _data.data();
    }
    
};

#endif //MINILA_VECTOR_H
