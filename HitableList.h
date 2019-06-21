//
// Created by Ognjen on 04.05.2019.
//

#ifndef RAY_TRACER_HITABLELIST_H
#define RAY_TRACER_HITABLELIST_H

#include "Hitable.h"

class HitableList : public Hitable {
public:
    HitableList() {}

    HitableList(Hitable **l, int n) {
        list = l;
        list_size = n;
    }

    virtual bool hit(const Ray &ray, double t_min, double t_max, hit_record &record) const;

    Hitable **list;
    int list_size;
};

bool HitableList::hit(const Ray &ray, double t_min, double t_max, hit_record &record) const {
    hit_record current_record;
    bool hit_anything = false;
    double closest_so_far = t_max;
    for (int i = 0; i < list_size; i++) {
        if (list[i]->hit(ray, t_min, closest_so_far, current_record)) {
            hit_anything = true;
            closest_so_far = current_record.t;
            record = current_record;
        }
    }
    return hit_anything;
}

#endif //RAY_TRACER_HITABLELIST_H
