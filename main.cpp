#include "Object.h"
#include "Camera.h"
#include "Light.h"
#include "read_json.h"
#include "write_ppm.h"
#include "viewing_ray.h"
#include "raycolor.h"
#include <Eigen/Core>
#include <vector>
#include <iostream>
#include <memory>
#include <limits>
#include <functional>
#include "read_rgba_from_png.h"
#include "rgba_to_rgb.h"

int main(int argc, char * argv[])
{
  Camera camera;
  std::vector< std::shared_ptr<Object> > objects;
  std::vector< std::shared_ptr<Light> > lights;

  std::vector<std::vector<unsigned char>> textures;
  std::vector<int> texture_height_offsets;
  bool use_textures = false;

  std::string outputname;

  if (argc == 2 && strcmp(argv[1], "texture") == 0)
  {
    outputname = "textured_seattle.ppm";
    use_textures = true;
    // Read a camera and scene description from given .json file
    read_json(
      "../shared/data/seattle-postcard.json",
      camera,
      objects,
      lights);

    // read texture files
    const char * default_input_file_names[] {
      "../images/seattle_skyline.png",
      "../images/floor_texture.png"
    };
    char ** input_file_names = const_cast<char **>(default_input_file_names);

    // background texture
    int background_width, background_height;
    std::vector<unsigned char> background_rgba;
    read_rgba_from_png(input_file_names[0], background_rgba, background_width, background_height);

    std::vector<unsigned char> background_rgb;
    rgba_to_rgb(background_rgba, background_width, background_height, background_rgb);
    textures.push_back(background_rgb);
    texture_height_offsets.push_back(background_height - 1);

    std::shared_ptr<Plane> background(new Plane());
    background->texture_id = 0;
    background->point = Eigen::Vector3d(0,0,-5);
    background->normal = Eigen::Vector3d(0,0,1).normalized();
    objects.push_back(background);

    // floor texture
    int floor_width, floor_height;
    std::vector<unsigned char> floor_rgba;
    read_rgba_from_png(input_file_names[1], floor_rgba, floor_width, floor_height);
    std::vector<unsigned char> floor_rgb; 
    rgba_to_rgb(floor_rgba, floor_width, floor_height, floor_rgb);
    textures.push_back(floor_rgb);
    texture_height_offsets.push_back(floor_height - 1);
   
    std::shared_ptr<Plane> floor_plane(new Plane());
    floor_plane->texture_id = 1;
    floor_plane->point = Eigen::Vector3d(0,-1,0);
    floor_plane->normal = Eigen::Vector3d(0,1,0).normalized();
    objects.push_back(floor_plane);
  }
  else
  {
    // Read a camera and scene description from given .json file
    read_json(
      "../shared/data/untextured-seattle-postcard.json",
      camera,
      objects,
      lights);
    outputname = "untextured_seattle.ppm";
  }

  int width =  640;
  int height = 360;
  std::vector<unsigned char> rgb_image(3*width*height);
  // For each pixel (i,j)
  for(unsigned i=0; i<height; ++i) 
  {
    for(unsigned j=0; j<width; ++j)
    {
      // Set background color
      Eigen::Vector3d rgb(0,0,0);

      // Compute viewing ray
      Ray ray;
      viewing_ray(camera,i,j,width,height,ray);
      
      // Shoot ray and collect color
      if (raycolor(ray,1.0,objects,lights,0, i, j, textures, texture_height_offsets, rgb))
      {
        // Write double precision color into image
        auto clamp = [](double s){ return std::max(std::min(s,1.0),0.0);};
        rgb_image[0+3*(j+width*i)] = 255.0*clamp(rgb(0));
        rgb_image[1+3*(j+width*i)] = 255.0*clamp(rgb(1));
        rgb_image[2+3*(j+width*i)] = 255.0*clamp(rgb(2));
      }
      else
      {
        rgb_image[0+3*(j+width*i)] = rgb(0);
        rgb_image[1+3*(j+width*i)] = rgb(1);
        rgb_image[2+3*(j+width*i)] = rgb(2);
      }
    }
  }

  write_ppm(outputname, rgb_image, width, height, 3);
}
