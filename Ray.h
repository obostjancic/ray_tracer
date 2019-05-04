//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_RAY_H
#define RAY_TRACER_RAY_H

#include "Vector3D.h"

class Ray
{
public:
    Ray() {}
    Ray(const Vector3D& a, const Vector3D& b) { A = a; B = b; }
    Vector3D origin() const       { return A; }
    Vector3D direction() const    { return B; }
    Vector3D point_at_parameter(float t) const { return A + t * B; }

    Vector3D A;
    Vector3D B;
};

#endif //RAY_TRACER_RAY_H
