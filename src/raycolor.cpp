#include "raycolor.h"
#include "first_hit.h"
#include "blinn_phong_shading.h"
#include "reflect.h"
#include "Plane.h"
#include <iostream>
#include <get_texture_colour.h>

bool raycolor(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector< std::shared_ptr<Light> > & lights,
  const int num_recursive_calls,
  const int current_i_pixel,
  const int current_j_pixel,
  const std::vector<std::vector<unsigned char>> & textures,
  const std::vector<int> & texture_height_offsets,
  Eigen::Vector3d & rgb)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  if (num_recursive_calls == 2)
  {
    return false;
  }
  rgb = Eigen::Vector3d(0,0,0);
  Eigen::Vector3d Ia = Eigen::Vector3d(1,1,1);
  Eigen::Vector3d reflection_rgb; 
  int hit_id;
  double t;
  Eigen::Vector3d n;

  std::shared_ptr<Object> current_obj;
  Eigen::Vector3d point;
  std::vector< std::shared_ptr<Light> > current_light;
  Eigen::Vector3d v_n;
  Eigen::Vector3d l;
  double l_t;
  Eigen::Vector3d l_n;

  // Shadow ray
  Eigen::Vector3d shadow_point;
  Ray shadow;
  int shadow_hit;
  double shadow_t;
  Eigen::Vector3d shadow_n;
  double epsilon;

  Eigen::Vector3d reflection;
  Ray reflection_ray;
  int reflection_hit;
  double reflection_t;
  Eigen::Vector3d reflection_n;

  if (first_hit(ray, min_t, objects, hit_id, t, n))
  {
    current_obj = objects[hit_id];
    point = ray.origin + (t * ray.direction);
    v_n = (-ray.direction).normalized();

    // determine if current object is a textured plane
    if (std::dynamic_pointer_cast<Plane>(current_obj))
    {
      std::shared_ptr<Plane> textured_plane = std::dynamic_pointer_cast<Plane>(current_obj);
      if (textured_plane->texture_id > -1)
      {
        std::vector<unsigned char> current_texture = textures[textured_plane->texture_id];
        int height_offset = texture_height_offsets[textured_plane->texture_id];
        rgb = get_texture_colour(current_texture, current_i_pixel, current_j_pixel, height_offset);
        return false;
      }
    }
    else
    {
      rgb = (current_obj->material->ka.array() * Ia.array()).matrix();
    }

    for (std::vector<std::shared_ptr<Light>>::const_iterator it = lights.begin(); it != lights.end(); ++it)
    {
      current_light.clear();
      current_light.push_back(*it);
      (*it)->direction(point, l, l_t);
      shadow = {point, l};

      if (l_t == std::numeric_limits<double>::infinity())
      {
        epsilon = 0.001f;
      }
      else
      {
        epsilon = l_t / 1000;
      }

      if (!first_hit(shadow, epsilon, objects, shadow_hit, shadow_t, shadow_n))
      {
        rgb += blinn_phong_shading(ray, hit_id, t, n, objects, current_light);
        reflection = reflect(v_n, n);
        reflection_ray = {point, reflection};
        
        if (raycolor(reflection_ray, epsilon, objects, lights, num_recursive_calls + 1, 
          current_i_pixel, current_j_pixel, textures, texture_height_offsets, reflection_rgb))
        {
          rgb += (current_obj->material->km.array() * reflection_rgb.array()).matrix();
        }
      }
    }

    return true;
  }

  return true;
  ////////////////////////////////////////////////////////////////////////////
}
