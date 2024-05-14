#ifndef HITTABLE_H
#define HITTABLE_H

#include "main_header.h"
<<<<<<< HEAD

=======
>>>>>>> cac693248b7c61ab7a7cd704a216756d8d2c0806
class hit_record{
public:
    point3 p;
    vec3 normal;
    double t;
<<<<<<< HEAD

    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal) {
        // Sets the hit record normal vector.
        // NOTE: the parameter `outward_normal` is assumed to have unit length.

        front_face = dot(r.direction(), outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    };

=======
    bool front_face;

    void set_face_normal(const ray& r, const vec3& outward_normal){
        // NOTE: assume outward_normal to be unit vector
        // sets the hit record normal vector

        front_face = dot(r.direction , outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
>>>>>>> cac693248b7c61ab7a7cd704a216756d8d2c0806
};

class hittable {
  public:
    virtual ~hittable() = default;

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};


#endif
