#ifndef MATERIAL_H
#define MATERIAL_H

#include "main_header.h"
class hit_record;

class material{
public:
    virtual ~material() = default;
    virtual bool scatter(
        const ray& r_in , const hit_record& rec, color& attenuation,  ray& scattered
    ) const {
        return false;
    }
};
class lambertian : public material{
public:
    lambertian(const color& albedo): albedo(albedo) {};

    bool scatter(const ray& r_in , const hit_record& rec, color& attenuation , ray& scattered)
    const override {
        auto scatter_direction = rec.normal + random_unit_vector();
        // Catch degenerate scatter direction
        if (scatter_direction.near_zero())
            scatter_direction = rec.normal;
        scattered = ray(rec.p , scatter_direction);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};
class metal: public material{

public:
    metal(const color& albedo) : albedo(albedo) {}

    bool scatter(const ray& r_in , const hit_record& rec, color& attenuation , ray& scattered) const override {

        vec3 reflected = reflect(r_in.direction(), rec.normal);
        scattered = ray(rec.p , reflected);
        attenuation = albedo;
        return true;
    }
private:
    color albedo;
};

class dielectric: public material{
public:
    dielectric(double refraction_index) : refraction_index(refraction_index) {}
    bool scatter(const ray& r_in, const hit_record& rec, color& attenuation,ray& scattered) const override {
        attenuation = color(1.0,1.0,1.0);
        double ri = rec.front_face ? (1/refraction_index) : refraction_index;
        vec3 unit_direction = unit_vector(r_in.direction());
        vec3 refracted = refract(unit_direction , rec.normal , ri);
        scattered = ray(rec.p , refracted);
        return true;
    }

private:
    double refraction_index;
};
#endif // MATERIAL_H
