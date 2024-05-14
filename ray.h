#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
private:
    vec3 orig;
    vec3 dir;

public:
    ray() {}
    ray(const point3& origin , point3& direction) : orig(origin), dir(direction) {}

    const point3& origin() const {return orig;}
    const point3& direction() const {return dir;}

    point3 at(double t) const {
        return orig + t*dir;
    }
};

#endif
