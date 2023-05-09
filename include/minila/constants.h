/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#ifndef MINILA_CONSTANTS_H
#define MINILA_CONSTANTS_H

namespace minila {

    double_t MINILA_SVD_RANK = 1e-6; // Minimum singular value to be considered numerically != 0.

};

namespace minila::numerical {

    double_t MINILA_DX_PRECISION = 1e-6; // Derivative precision
    double_t MINILA_RT_PRECISION = 1e-6; // Root finding precision
    uint8_t MINILA_DX_ORDER = 4; // Derivative order to use; Accepts 4 or 2.
    uint16_t MINILA_MAXITER = 10000; // Maximum number of iterations

};

namespace minila::integration {

    uint32_t MINILA_SIMPSON = 100000; // Number of subdivisions for integration
    uint32_t MINILA_SIMPSON_38 = 99999; // Number of subdivisions for integration
    uint32_t MINILA_TRAPEZIUM = 100000; // Number of subdivisions for integration

};

#endif //MINILA_CONSTANTS_H
