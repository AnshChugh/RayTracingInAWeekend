#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

<<<<<<< HEAD
#include "hittable.h"


#include <vector>
=======
#include "main_header.h"
>>>>>>> cac693248b7c61ab7a7cd704a216756d8d2c0806


class hittable_list : public hittable{
public:
    std::vector<shared_ptr<hittable>> objects;

    hittable_list(){};

    hittable_list(shared_ptr<hittable> object){add(object);};

    void clear(){objects.clear();};

    void add(shared_ptr<hittable> object){
        objects.push_back(object);
    }

    bool hit(const ray& r, double ray_tmin , double ray_tmax , hit_record& rec) const override {
        hit_record temp_record;
        bool hit_anything = false;
        auto closest_so_far = ray_tmax;

        for(const auto& object: objects){
            if(object->hit(r, ray_tmin ,ray_tmax, temp_record) && temp_record.t <= closest_so_far){
                hit_anything = true;
                closest_so_far = temp_record.t;
                rec = temp_record;
            }
        }
        return hit_anything;
    }

};

#endif // HITTABLE_LIST_H
