//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Hitable.h"

class Sphere: public Hitable  {
public:
    Sphere() {}
    Sphere(Vector3D center, float radius) : center(center), radius(radius) {};
    virtual bool hit(const Ray& ray, float t_min, float t_max, hit_record& rec) const;
    Vector3D center;
    float radius;
};

bool Sphere::hit(const Ray& ray, float t_min, float t_max, hit_record& record) const {
    Vector3D oc = ray.origin() - center;
    float a = dot(ray.direction(), ray.direction());
    float b = dot(oc, ray.direction());
    float c = dot(oc, oc) - radius*radius;
    float discriminant = b*b - a*c;
    if (discriminant > 0) {
        float temp = (-b - sqrt(discriminant))/a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACER_SPHERE_H
