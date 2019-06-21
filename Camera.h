//
// Created by Ognjen on 08.05.2019.
//

#ifndef RAY_TRACER_CAMERA_H
#define RAY_TRACER_CAMERA_H

#include "Ray.h"
#include "Util.h"

Vector3D random_in_unit_disk() {
    Vector3D p;
    do {
        p = 2.0 * Vector3D(random(), random(), 0) - Vector3D(1, 1, 0);
    } while (dot(p, p) >= 1.0);
    return p;
}

class Camera {
public:
    Camera() {
        this->origin = Vector3D();
        this->lower_left_corner = Vector3D();
        this->horizontal = Vector3D();
        this->vertical = Vector3D();
        this->u = Vector3D();
        this->v = Vector3D();
        this->w = Vector3D();
        this->lens_radius = 0;
    }
    Camera(Vector3D lookfrom, Vector3D lookat, Vector3D vup, double vfov, double aspect, double aperture,
           double focus_dist) { // vfov is top to bottom in degrees
        lens_radius = aperture / 2;
        double theta = vfov * M_PI / 180;
        double half_height = tan(theta / 2);
        double half_width = aspect * half_height;
        origin = lookfrom;
        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);
        lower_left_corner = origin - half_width * focus_dist * u - half_height * focus_dist * v - focus_dist * w;
        horizontal = 2 * half_width * focus_dist * u;
        vertical = 2 * half_height * focus_dist * v;
    }

    Ray get_ray(double s, double t) {
        Vector3D rd = lens_radius * random_in_unit_disk();
        Vector3D offset = u * rd.x() + v * rd.y();
        return Ray(origin + offset, lower_left_corner + s * horizontal + t * vertical - origin - offset);
    }

    Vector3D origin;
    Vector3D lower_left_corner;
    Vector3D horizontal;
    Vector3D vertical;
    Vector3D u, v, w;
    double lens_radius;
};

#endif //RAY_TRACER_CAMERA_H
