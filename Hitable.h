//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_HITABLE_H
#define RAY_TRACER_HITABLE_H

#include "Ray.h"

struct hit_record {
    float t;
    Vector3D p;
    Vector3D normal;
};

class Hitable {
public:
    virtual bool hit(const Ray &ray, float t_min, float t_max, hit_record &rec) const = 0;
};

#endif //RAY_TRACER_HITABLE_H
