#include <iostream>
#include <fstream>
#include <limits>
#include "Vector3D.h"
#include "Ray.h"
#include "Hitable.h"
#include "Sphere.h"
#include "Camera.h"
#include "HitableList.h"
#include "Material.h"
#include "Util.h"
#include "Ellipsoid.h"
#include "Parser.h"
using namespace std;


Vector3D color(const Ray &ray, Hitable *world, int depth) {
    hit_record record;
    double MAXFLOAT = numeric_limits<double>::max();
    if (world->hit(ray, 0.001, MAXFLOAT, record)) {
        Ray scattered;
        Vector3D attenuation;
        if (depth < 50 && record.mat_ptr->scatter(ray, record, attenuation, scattered)) {
            return attenuation * color(scattered, world, depth + 1);
        } else {
            return Vector3D(0, 0, 0);
        }
    } else {
        Vector3D unit_direction = unit_vector(ray.direction());
        double t = 0.5 * (unit_direction.y() + 1.0);
        return (1.0 - t) * Vector3D(1.0, 1.0, 1.0) + t * Vector3D(0.5, 0.7, 1.0);
    }
}

int main() {

    ofstream fout;
    fout.open("out.ppm");

    int nx, ny, ns;
    Camera cam;
    Hitable *world = parse_scene("scene.txt", nx, ny, ns, cam);

    fout << "P3\n" << nx << " " << ny << "\n255\n";

    for (int j = ny - 1; j >= 0; j--) {
        for (int i = 0; i < nx; i++) {
            Vector3D col(0.0, 0.0, 0.0);
            for (int s = 0; s < ns; s++) {
                double u = (i + random()) / double(nx);
                double v = (j + random()) / double(ny);

                Ray ray = cam.get_ray(u, v);
                Vector3D p = ray.point_at_parameter(2.0);
                col += color(ray, world, 0);
            }

            col /= double(ns);
            col = Vector3D(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
            int ir = int(255.99 * col[0]);
            int ig = int(255.99 * col[1]);
            int ib = int(255.99 * col[2]);

            fout << ir << " " << ig << " " << ib << "\n";
        }
    }

    fout.close();
}