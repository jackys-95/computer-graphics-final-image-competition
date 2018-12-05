#include "blinn_phong_shading.h"
// Hint:
#include "first_hit.h"
#include <iostream>
#include <cmath>

Eigen::Vector3d blinn_phong_shading(
  const Ray & ray,
  const int & hit_id, 
  const double & t,
  const Eigen::Vector3d & n,
  const std::vector< std::shared_ptr<Object> > & objects,
  const std::vector<std::shared_ptr<Light> > & lights)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  Eigen::Vector3d colour = Eigen::Vector3d(0, 0, 0);
  std::shared_ptr<Object> current_obj = objects[hit_id];
  std::shared_ptr<Light> current_light = lights[0];
  Eigen::Vector3d point = ray.origin + (t * ray.direction);

  Eigen::Vector3d v = (-ray.direction).normalized();
  Eigen::Vector3d l;
  double l_t;
  current_light->direction(point, l, l_t);
  Eigen::Vector3d l_n = l.normalized();

  Eigen::Vector3d h = (v + l_n) / (v + l_n).norm();

  double n_dot_l = n.dot(l_n);
  Eigen::Vector3d diffuse = (current_obj->material->kd.array() * current_light->I.array()).matrix() 
    * fmax(0, n_dot_l);

  Eigen::Vector3d specular = ((current_obj->material->ks.array() * current_light->I.array()).matrix() 
    * pow(n.dot(h), current_obj->material->phong_exponent));
  colour = diffuse + specular;

  return colour;
  ////////////////////////////////////////////////////////////////////////////
}
