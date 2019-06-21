//
// Created by Ognjen on 20.06.2019.
//

#ifndef RAY_TRACER_UTIL_H
#define RAY_TRACER_UTIL_H

#include <limits>
#include <random>

double random() {
    return static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / 0.9999999999999));
}

const double M_PI = 3.1415926535;

#endif //RAY_TRACER_UTIL_H
