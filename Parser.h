//
// Created by Ognjen on 21.06.2019.
//

#ifndef RAY_TRACER_PARSER_H
#define RAY_TRACER_PARSER_H

#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<string> split(string str, char separator) {
    vector<string> res = vector<string>();
    string curr_str = "";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == separator) {
            res.push_back(curr_str);
            curr_str = "";
        } else
            curr_str += str[i];
    }
    res.push_back(curr_str);
    return res;
}

Vector3D parse_vector(string str) {
    vector<string> splitted = split(str, ',');
    double x = stod(splitted[0]);
    double y = stod(splitted[1]);
    double z = stod(splitted[2]);

    return {x, y, z};
}

void parse_dimensions(string line, int &nx, int &ny, int &ns){
    cout << "--------------------------------------------------------------- " << endl;
    cout << "Reading dimensions" << endl;
    vector<string> splitted = split(line, ' ');
    nx = stoi(splitted[0]);
    ny = stoi(splitted[1]);
    ns = stoi(splitted[2]);
    cout << "Width: " << nx << " pixels, height " << ny << " pixels" << endl;
    cout << "Number of samples per pixel: " << ns << endl;
}

Camera parse_camera(string line, int nx, int ny){
    cout << "--------------------------------------------------------------- " << endl;
    cout << "Reading camera settings" << endl;
    vector<string> splitted = split(line, ' ');
    Vector3D lookfrom = parse_vector(splitted[0]);
    Vector3D lookat = parse_vector(splitted[1]);
    double dist_to_focus = stod(splitted[2]);
    double aperture = stod(splitted[3]);
    cout << "Camera positioned at: " << lookfrom << ", and looking at: " << lookat << endl;
    cout << "Distance to focus: " << dist_to_focus << ", aperture: " << aperture << endl;
    return {lookfrom, lookat, Vector3D(0, 1, 0), 20, double(nx) / double(ny), aperture, dist_to_focus};
}

Material* parse_material(vector<string> mat_vec) {
    cout << "Reading material ";
    if(mat_vec[0] == "L"){
        cout << "Lambertian: " << mat_vec[1] << endl;
        return new lambertian(parse_vector(mat_vec[1]));
    }
    else if (mat_vec[0] == "D"){
        cout << "Dielectric: " << mat_vec[1] << endl;
        return new dielectric(stod(mat_vec[1]));
    }
    else {
        cout << "Metal: " << mat_vec[1] << ", " << mat_vec[2] << endl;
        return new metal(parse_vector(mat_vec[1]), stod(mat_vec[2]));
    }
}

Sphere* parse_sphere(string line) {
    cout << "Sphere" << endl;
    vector<string> splitted = split(line, ' ');
    Vector3D center = parse_vector(splitted[1]);
    cout << "Center at " << center << ", ";
    double radius = stod(splitted[2]);
    cout << "Radius: " << radius << endl;
    vector<string> mat_vec = vector<string>(splitted.begin()+ 3, splitted.begin() + splitted.size());
    Material * mat_ptr = parse_material(mat_vec);
    return new Sphere(center, radius, mat_ptr);
}

Ellipsoid* parse_ellipsoid(string line) {
    cout << "Ellipsoid" << endl;
    vector<string> splitted = split(line, ' ');
    Vector3D center = parse_vector(splitted[1]);
    cout << "Center at " << center << ", ";
    double x_semiaxis = stod(splitted[2]);
    double y_semiaxis = stod(splitted[3]);
    double z_semiaxis = stod(splitted[4]);
    cout << "Semi axes: " << x_semiaxis << ", " << y_semiaxis << ", " << z_semiaxis << endl;
    vector<string> mat_vec = vector<string>(splitted.begin()+ 5, splitted.begin() + splitted.size());
    Material * mat_ptr = parse_material(mat_vec);
    return new Ellipsoid(center, x_semiaxis, y_semiaxis, z_semiaxis, mat_ptr);
}

Hitable* parse_hitable(string line) {
    cout << "--------------------------------------------------------------- " << endl;
    cout << "Reading hitable ";
    if (line[0] == 'S')
        return parse_sphere(line);
    else if (line[0] == 'E')
        return parse_ellipsoid(line);
}

Hitable* parse_scene(string filename, int &nx, int &ny, int &ns, Camera &cam) {
    string line;
    ifstream file("scene.txt");
    if (file.is_open()){
        cout << "Reading scene from " << filename << endl;
        getline(file,line);
        parse_dimensions(line, nx, ny, ns);
        getline(file,line);
        cam = parse_camera(line, nx, ny);
        getline(file,line);
        int num_of_hitables = stoi(line);
        cout << "--------------------------------------------------------------- " << endl;
        cout << "Scene contains " << num_of_hitables << " hitable objects" << endl;
        Hitable** list = new Hitable*[num_of_hitables];
        int i = 0;
        while (getline(file,line)) {
            list[i] = parse_hitable(line);
            i++;
        }
        file.close();
        cout << "--------------------------------------------------------------- " << endl;
        cout << "                            COMPLETED" << endl;
        cout << "--------------------------------------------------------------- " << endl;
        return new HitableList(list, num_of_hitables);
    }

    else cout << "Unable to open file";
}

#endif //RAY_TRACER_PARSER_H
