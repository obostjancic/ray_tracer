//
// Created by Ognjen on 20.06.2019.
//

#ifndef RAY_TRACER_MATERIAL_H
#define RAY_TRACER_MATERIAL_H

struct hit_record;

#include "Ray.h"
#include "Hitable.h"
#include "Util.h"

double schlick(double cosine, double ref_idx) {
    double r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0 * r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

bool refract(const Vector3D &v, const Vector3D &n, double ni_over_nt, Vector3D &refracted) {
    Vector3D uv = unit_vector(v);
    double dt = dot(uv, n);
    double discriminant = 1.0 - ni_over_nt * ni_over_nt * (1 - dt * dt);
    if (discriminant > 0) {
        refracted = ni_over_nt * (uv - n * dt) - n * sqrt(discriminant);
        return true;
    } else
        return false;
}

Vector3D reflect(const Vector3D &v, const Vector3D &n) {
    return v - 2 * dot(v, n) * n;
}

Vector3D random_in_unit_sphere() {
    Vector3D p;
    do {
        p = 2.0 * Vector3D(random(), random(), random()) - Vector3D(1, 1, 1);
    } while (p.squared_length() >= 1.0);
    return p;
}

class Material {
public:
    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vector3D &attenuation, Ray &scattered) const = 0;
};

class lambertian : public Material {
public:
    lambertian(const Vector3D &a) : albedo(a) {}

    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vector3D &attenuation, Ray &scattered) const {
        Vector3D target = rec.p + rec.normal + random_in_unit_sphere();
        scattered = Ray(rec.p, target - rec.p);
        attenuation = albedo;
        return true;
    }

    Vector3D albedo;
};

class metal : public Material {
public:
    metal(const Vector3D &a, double f) : albedo(a) { if (f < 1) fuzz = f; else fuzz = 1; }

    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vector3D &attenuation, Ray &scattered) const {
        Vector3D reflected = reflect(unit_vector(r_in.direction()), rec.normal);
        scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
        attenuation = albedo;
        return (dot(scattered.direction(), rec.normal) > 0);
    }

    Vector3D albedo;
    double fuzz;
};

class dielectric : public Material {
public:
    dielectric(double ri) : ref_idx(ri) {}

    virtual bool scatter(const Ray &r_in, const hit_record &rec, Vector3D &attenuation, Ray &scattered) const {
        Vector3D outward_normal;
        Vector3D reflected = reflect(r_in.direction(), rec.normal);
        double ni_over_nt;
        attenuation = Vector3D(1.0, 1.0, 1.0);
        Vector3D refracted;
        double reflect_prob;
        double cosine;
        if (dot(r_in.direction(), rec.normal) > 0) {
            outward_normal = -rec.normal;
            ni_over_nt = ref_idx;
            //         cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
            cosine = dot(r_in.direction(), rec.normal) / r_in.direction().length();
            cosine = sqrt(1 - ref_idx * ref_idx * (1 - cosine * cosine));
        } else {
            outward_normal = rec.normal;
            ni_over_nt = 1.0 / ref_idx;
            cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
        }
        if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted))
            reflect_prob = schlick(cosine, ref_idx);
        else
            reflect_prob = 1.0;
        if (random() < reflect_prob)
            scattered = Ray(rec.p, reflected);
        else
            scattered = Ray(rec.p, refracted);
        return true;
    }

    double ref_idx;
};

#endif //RAY_TRACER_MATERIAL_H
