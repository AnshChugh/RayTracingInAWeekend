#ifndef SPHERE_H
#define SPHERE_H

#include "main_header.h"

class sphere : public hittable {
public:
     sphere(const point3& center, double radius) : center(center) , radius(fmax(0,radius)){}

     bool hit(const ray& r,double ray_tmin, double ray_tmax, hit_record& rec)const  override {
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
        rec.set_face(r , outward_normal);
     }
private:
    point3 center;
    double radius;
};


#endif // SPHERE_H
