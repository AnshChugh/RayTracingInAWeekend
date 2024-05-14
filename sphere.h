#ifndef SPHERE_H
#define SPHERE_H

#include "main_header.h"

class sphere : public hittable {
public:
     sphere(const point3& center, double radius) : center(center) , radius(fmax(0,radius)){}

<<<<<<< HEAD
     bool hit(const ray& r,double tmin, double tmax, hit_record& rec)const  override {
=======
     bool hit(const ray& r,double ray_tmin, double ray_tmax, hit_record& rec)const  override {
>>>>>>> cac693248b7c61ab7a7cd704a216756d8d2c0806
        // substituting b = -2h we get these simpler formulas
        auto oc = center - r.origin();
        auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        auto c = oc.length_squared() - radius*radius;
        auto discriminant = h*h - a*c;
        if(discriminant < 0) return false;

        auto sqrtd = sqrt(discriminant);

        // find nearest root that lies in acceptable range
        auto root = (h - sqrtd) / a;
        if(root <= tmin || root >= tmax){
            root = (h + sqrtd) / a;
            if(root <= tmin || root >= tmax)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
<<<<<<< HEAD
        rec.set_face_normal(r , outward_normal);

        return true;
=======
        rec.set_face(r , outward_normal);
>>>>>>> cac693248b7c61ab7a7cd704a216756d8d2c0806
     }
private:
    point3 center;
    double radius;
};


#endif // SPHERE_H
