#include <iostream>
#include <fstream>
#include <limits>
#include "Vector3D.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "HitableList.h"

using namespace std;

//float hit_sphere(const Vector3D& center, float radius, const Ray& ray) {
//    Vector3D oc = ray.origin() - center;
//    float a = dot(ray.direction(), ray.direction());
//    float b = 2.0 * dot(oc, ray.direction());
//    float c = dot(oc, oc) - radius * radius;
//    float discriminant = b * b - 4 * a * c;
//
//    if (discriminant < 0)
//        return -1.0;
//    else
//        return (-b - sqrt(discriminant)) / (2.0 * a);
//}

Vector3D color(const Ray &ray, Hitable *world) {
    hit_record record;
    float MAXFLOAT = numeric_limits<float>::max();
    if (world->hit(ray, 0.0, MAXFLOAT, record)) {
        return 0.5 * Vector3D(record.normal.x() + 1, record.normal.y() + 1, record.normal.z() + 1);
    } else {
        Vector3D unit_direction = unit_vector(ray.direction());
        float t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3D(1.0, 1.0, 1.0) + t * Vector3D(0.5, 0.7, 1.0);
    }
}

int main() {

    ofstream fout;
    fout.open("out.ppm");

    int nx = 800, ny = 400;
    fout << "P3\n" << nx << " " << ny << "\n255\n";

    Vector3D lower_left_corner(-2.0, -1.0, -1.0);
    Vector3D horizontal(4.0, 0.0, 0.0);
    Vector3D vertical(0.0, 2.0, 0.0);
    Vector3D origin(0.0, 0.0, 0.0);

    Hitable *list[2];
    list[0] = new Sphere(Vector3D(0, 0, -1), 0.5);
    list[1] = new Sphere(Vector3D(0, -100.5, -1), 100);

    Hitable *world = new HitableList(list, 2);
    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {

            float u = float(i) / float(nx);
            float v = float(j) / float(ny);

            Ray ray(origin, lower_left_corner + u * horizontal + v * vertical);
            Vector3D p = ray.point_at_parameter(2.0);
            Vector3D col = color(ray, world);

            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            fout << ir << " " << ig << " " << ib << "\n";
        }
    }

    fout.close();
}