/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#include <iostream>
#include "include/minila/minila.h"

using namespace minila;
using namespace std;

int main() {

    auto A = Matrix<float>(100, 100);

    for (uint64_t i = 1; i <= A.rows(); i++)
        for (uint64_t j = 1; j <= A.cols(); j++)
            A(i, j) = i + j;

    return 0;
}