/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_ARRAY_DEFINITION_H
#define MINILA_ARRAY_DEFINITION_H

#include <concepts>

namespace minila
{

    template<typename T> requires std::is_floating_point_v<T>
    class Array
    {
    public:
        Array();
        virtual ~Array();
    private:
        T *values;
    };

    template<typename T>
    requires std::is_floating_point_v<T>
    Array<T>::Array()
    {
        values = nullptr;
    }

    template<typename T>
    requires std::is_floating_point_v<T>
    Array<T>::~Array()
    {
        delete[] values;
    }

}

#endif //MINILA_ARRAY_DEFINITION_H
