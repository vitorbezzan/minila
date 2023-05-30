/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#include "include/minila/minila.h"

template class minila::Matrix<float>;
template class minila::Matrix<double>;

template class minila::Vector<float>;
template class minila::Vector<double>;

template class minila::SVD<float>;
template class minila::SVD<double>;

template class minila::LU<float>;
template class minila::LU<double>;

template class minila::process::Process<float>;
template class minila::process::Process<double>;

template class minila::process::Brownian<float>;
template class minila::process::Brownian<double>;

template class minila::process::Geometric<float>;
template class minila::process::Geometric<double>;
