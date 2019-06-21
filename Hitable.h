//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_HITABLE_H
#define RAY_TRACER_HITABLE_H

#include "Ray.h"

class Material;

struct hit_record {
    double t;
    Vector3D p;
    Vector3D normal;
    Material *mat_ptr;
};

class Hitable {
public:
    virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &rec) const = 0;
};

#endif //RAY_TRACER_HITABLE_H
