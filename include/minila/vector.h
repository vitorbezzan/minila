/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_VECTOR_H
#define MINILA_VECTOR_H

#include <numeric>
#include <cmath>

namespace minila {

    template<typename Type>
    class Vector {

    public:
        friend class Vector;

        Vector() : _data(BaseArray < Type > ()), _dimensions(0) {}
        Vector(const Vector<Type> &right);
        explicit Vector(BaseArray <Type> &right);
        explicit Vector(uint64_t dimensions);

        Type &operator()(uint64_t dimension);
        Vector<Type> operator+(const Vector<Type> &right);
        Vector<Type> operator-(const Vector<Type> &right);

        uint64_t dimensions();
        Type *data();

    private:
        BaseArray <Type> _data;
        uint64_t _dimensions;
    };

    template<typename Type>
    Vector<Type>::Vector(const Vector<Type> &right) {
        _dimensions = right._dimensions;
        _data = right._data;
    }

    template<typename Type>
    Vector<Type>::Vector(BaseArray<Type> &right) {
        _dimensions = right[0];
        _data = right;
    }

    template<typename Type>
    Vector<Type>::Vector(uint64_t dimensions) {
        _dimensions = dimensions;
        _data = BaseArray < Type > ({ dimensions, });
    }

    template<typename Type>
    Type &Vector<Type>::operator()(uint64_t dimension) {
        return _data({dimension - 1,});
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
    uint64_t Vector<Type>::dimensions() {
        return _dimensions;
    }

    template<typename Type>
    Type *Vector<Type>::data() {
        return _data.data();
    }

    namespace naive{

        template<typename T1, typename T2>
        inline auto dot(Vector<T1> &left, Vector<T2> &right)
        {
            if(left.dimensions() != right.dimensions())
                throw std::invalid_argument("Invalid axis sizes on operation dot.");

            using R = decltype(T1(0) * T2(0));
            R result = std::inner_product(left.data(), left.data() + left.dimensions(), right.data(), 0);

            return result;
        }

        template<typename T>
        inline auto abs(Vector<T> &left)
        {
            return dot(left, left);
        }

        template<typename T1, typename T2>
        inline auto cosine(Vector<T1> &left, Vector<T2> &right)
        {
            return dot(left, right) / (abs(left) * abs(right));
        }

        template<typename T1, typename T2>
        inline auto angle(Vector<T1> &left, Vector<T2> &right)
        {
            return std::acos(cosine(left, right));
        }
    };
};

#endif //MINILA_VECTOR_H
