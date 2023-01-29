/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_VECTOR_H
#define MINILA_VECTOR_H

namespace minila {

    template<typename Type>
    class Vector {

    public:
        friend class Vector;

        Vector() : _data(BaseArray < Type > ()), _rows(0) {}
        Vector(const Vector<Type> &right);
        explicit Vector(BaseArray <Type> &right);
        explicit Vector(uint64_t rows);

        Type &operator()(uint64_t row);
        Vector<Type> operator+(const Vector<Type> &right);
        Vector<Type> operator-(const Vector<Type> &right);

        uint64_t rows();
        Type *data();

    private:
        BaseArray <Type> _data;
        uint64_t _rows;
    };

    template<typename Type>
    Vector<Type>::Vector(const Vector<Type> &right) {
        _rows = right._rows;
        _data = right._data;
    }

    template<typename Type>
    Vector<Type>::Vector(BaseArray<Type> &right) {
        _rows = right[0];
        _data = right;
    }

    template<typename Type>
    Vector<Type>::Vector(uint64_t rows) {
        _rows = rows;
        _data = BaseArray < Type > ({ rows, });
    }

    template<typename Type>
    Type &Vector<Type>::operator()(uint64_t row) {
        return _data({row - 1,});
    }

    template<typename Type>
    Vector<Type> Vector<Type>::operator+(const Vector<Type> &right) {
        auto result = _data + right._data;
        return Vector<Type>(result);
    }

    template<typename Type>
    Vector<Type> Vector<Type>::operator-(const Vector<Type> &right) {
        auto result = _data - right._data;
        return Vector<Type>(result);
    }

    template<typename Type>
    uint64_t Vector<Type>::rows() {
        return _rows;
    }

    template<typename Type>
    Type *Vector<Type>::data() {
        return _data.data();
    }
};

#endif //MINILA_VECTOR_H
