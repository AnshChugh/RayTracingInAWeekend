#include "main_header.h"


color ray_color(const ray& r){
    auto t = hit_sphere(point3(0,0,-1),0.5,r);
    if(t > 0.0){
        vec3 N = unit_vector(r.at(t) - point3(0,0,-1));
        return 0.5 * color(N.x()+1 , N.y()+1 , N.z() + 1);
    }


    vec3 unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0-a)*color(1.0,1.0,1.0) + a * color(0.5,0.7,1.0);
}

int main(){

    auto aspect_ratio = 16.0/9.0;
    int image_width = 1024;

    // calculate image height and make sure it is atleast 1
    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    // camera
    // coordinate x to right y to top and -z to viewing side

    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/ image_height);
    auto camera_center = point3(0,0,0);

    // calculate the vectors across horizontal and down the vertical edges
    auto viewport_u = vec3(viewport_width , 0 , 0);
    auto viewport_v = vec3(0 , -viewport_height , 0);

    // horizontal and verticle delta vectors
    auto pixel_delta_u = viewport_u/image_width;
    auto pixel_delta_v = viewport_v/image_height;

    // calculate the location of upper left pixel
    // refer to diagram in the book for this part
    auto viewport_upper_left = camera_center - vec3(0,0, focal_length) - viewport_u/2 - viewport_v/2;
    auto pixel00loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    //render

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for(int j = 0; j < image_height ;j++){
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
        for(int i = 0; i< image_width; i++){
            auto pixel_center = pixel00loc + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center , ray_direction);

            color pixel_color = ray_color(r);
            write_color(std::cout , pixel_color);
        }
    }
    std::clog << "\rDone.               \n";

    return 0;
}
