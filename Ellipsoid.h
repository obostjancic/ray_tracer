//
// Created by Ognjen on 20.06.2019.
//

#ifndef RAY_TRACER_ELLIPSOID_H
#define RAY_TRACER_ELLIPSOID_H

#include "Hitable.h"

class Ellipsoid : public Hitable {
public:
    Ellipsoid() {}

    Ellipsoid(Vector3D center, double x_semiaxis, double y_semiaxis, double z_semiaxis, Material *material) :
    center(center), x_semiaxis(x_semiaxis), y_semiaxis(y_semiaxis), z_semiaxis(z_semiaxis), mat_ptr(material) {};

    virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &rec) const;

    Vector3D center;
    double x_semiaxis;
    double y_semiaxis;
    double z_semiaxis;
    Material *mat_ptr;
};

bool Ellipsoid::hit(const Ray &ray, double t_min, double t_max, hit_record &record) const {
    Vector3D oc = ray.origin() - center;
    Vector3D ocx = Vector3D(oc.x(), 0, 0);
    Vector3D ocy = Vector3D(0, oc.y(), 0);
    Vector3D ocz = Vector3D(0, 0, oc.z());
    Vector3D dirx = Vector3D(ray.direction().x(), 0, 0);
    Vector3D diry = Vector3D(0, ray.direction().y(), 0);
    Vector3D dirz = Vector3D(0, 0, ray.direction().z());
    double A = x_semiaxis, B = y_semiaxis, C = z_semiaxis;

    double a = B*B*C*C*dot(dirx, dirx) + A*A*C*C*dot(diry, diry) + A*A*B*B*dot(dirz, dirz);
    double b = B*B*C*C*dot(ocx, dirx) + A*A*C*C*dot(ocy, diry) + A*A*B*B*dot(ocz, dirz);
    double c = B*B*C*C*dot(ocx, ocx) + A*A*C*C*dot(ocy, ocy) + A*A*B*B*dot(ocz, ocz)- A*A*B*B*C*C;
    double discriminant = b * b - a * c;
    if (discriminant > 0) {
        double temp = (-b - sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = record.p - center;
            record.mat_ptr = mat_ptr;
            return true;
        }
        temp = (-b + sqrt(discriminant)) / a;
        if (temp < t_max && temp > t_min) {
            record.t = temp;
            record.p = ray.point_at_parameter(record.t);
            record.normal = record.p - center;
            record.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

#endif //RAY_TRACER_ELLIPSOID_H
