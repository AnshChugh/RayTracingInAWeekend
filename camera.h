#ifndef CAMERA_H
#define CAMERA_H

#include "main_header.h"
#include "hittable.h"
#include "material.h"




class camera{
public:
    double aspect_ratio = 1.0;
    int image_width = 100;
    int samples_per_pixel = 10;
    int max_depth = 10;

    double vfov = 90; // verticle view angle (field of view)
    point3 lookfrom = point3(0,0,0);
    point3 lookat = point3(0,0,-1);
    vec3 vup = vec3(0,1,0);

    // render
    void render(hittable_list& world){
        initialize();
        std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for(int j = 0; j < image_height ;j++){
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for(int i = 0; i< image_width; i++){
                color pixel_color(0,0,0);
                for(int samples = 0; samples < samples_per_pixel; samples++){
                    ray r = get_ray(i,j);
                    pixel_color += ray_color(r,max_depth,world);
                }
                write_color(std::cout,pixel_samples_scale * pixel_color);
            }
        }
        std::clog << "\rDone.               \n";
    }
private:

    int image_height;
    point3 camera_center;
    double pixel_samples_scale;
    point3 pixel00_loc;
    vec3 pixel_delta_u;
    vec3 pixel_delta_v;
    vec3 u, v, w;

    void initialize(){

        image_height = int(image_width/aspect_ratio);
        image_height = (image_height < 1) ? 1 : image_height;

        pixel_samples_scale = 1.0 / samples_per_pixel;


        // determine viewport dimensions
        auto focal_length = (lookfrom - lookat).length();
        auto theta = degrees_to_radians(vfov);
        auto h = tan(theta/2);
        auto viewport_height = 2 * h * focal_length;
        auto viewport_width = viewport_height * (double(image_width)/ image_height);
        camera_center = lookfrom;

        w = unit_vector(lookfrom - lookat);
        u = unit_vector(cross(vup, w));
        v = cross(w, u);

        // calculate the vectors across horizontal and down the vertical edges
        auto viewport_u = viewport_width * u;
        auto viewport_v = viewport_height * -v;

        // horizontal and verticle delta vectors
        pixel_delta_u = viewport_u/image_width;
        pixel_delta_v = viewport_v/image_height;

        // calculate the location of upper left pixel
        // refer to diagram in the book for this part
        auto viewport_upper_left = camera_center - (focal_length * w) - viewport_u/2 - viewport_v/2;
        pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
    }

    ray get_ray(int i ,int j) const {
        // Construct a camera ray originating from the origin and directed at randomly sampled
        // point around the pixel location i, j
        auto offset = sample_square();
        auto pixel_sample = pixel00_loc + ((i+offset.x()) * pixel_delta_u) + ((j + offset.y()) * pixel_delta_v);

        auto ray_origin = camera_center;
        auto ray_direction = pixel_sample - ray_origin;
        return ray(ray_origin, ray_direction);
    }

    vec3 sample_square() const {
        // Returns the vector to a random point in the [-.5,-.5]-[+.5,+.5] unit square.

        return vec3(random_double() - 0.5, random_double() - 0.5, 0);
    }
    color ray_color(const ray& r ,int max_depth, const hittable& world){

        if(max_depth < 1) return color(0,0,0);
        hit_record rec;
        if(world.hit(r,interval(0.001,infinity) , rec)){
            ray scattered;
            color attenuation;
            if(rec.mat->scatter(r,rec,attenuation,scattered)){
                return attenuation * ray_color(scattered , max_depth-1,world);
            }
            return color(0,0,0);
        }
        vec3 unit_direction = unit_vector(r.direction());
        auto a = 0.5*(unit_direction.y() + 1.0);
        return (1.0-a)*color(1.0, 1.0, 1.0) + a*color(0.5, 0.7, 1.0);
    }

};

#endif // CAMERA_H
