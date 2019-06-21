//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_SPHERE_H
#define RAY_TRACER_SPHERE_H

#include "Hitable.h"

class Sphere : public Hitable {
public:
    Sphere() {}

    Sphere(Vector3D center, double radius, Material *material) : center(center), radius(radius), mat_ptr(material) {};

    virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &rec) const;

    Vector3D center;
    double radius;
    Material *mat_ptr;
};

bool Sphere::hit(const Ray &ray, double t_min, double t_max, hit_record &record) const {
    Vector3D oc = ray.origin() - center;
    double a = dot(ray.direction(), ray.direction());
    double b = dot(oc, ray.direction());
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - a * c;
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = (record.p - center) / radius;
            record.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACER_SPHERE_H
