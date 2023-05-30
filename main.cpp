/*
 * Please check README.md for copyright and licensing.
 * If not available contact developer at vitor@bezzan.com
 * Code is distributed as-is without any guarantee of purpose.
 */

#include <iostream>
#include "include/minila/minila.h"

using namespace std;

int main()
{
    auto mean = minila::process::Process(0.001);
    auto sigma = minila::process::Process(0.05);

    auto p = minila::process::Geometric(20.0, &mean, &sigma);

    auto sequence = p.path(100, 42);

    for(int i = 0; i< 100; i++)
        std::cout<<(*sequence)[i]<<std::endl;

    return 0;
}