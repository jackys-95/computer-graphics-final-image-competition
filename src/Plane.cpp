#include "Plane.h"
#include "Ray.h"
#include <cmath>

bool Plane::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // vector form of a plane is: n \dot (r1 - r0) = 0
  // let r0 be given point for plane object
  // let r1 be some point from our ray: equation becomes n \dot ((e + td) - r0)
  // rearrange for t yields: ((r0 - e) \dot n) / (d \dot n)
  double t_prime = 0;
  double numerator = (point - ray.origin).dot(normal);
  double denominator = (ray.direction).dot(normal);
  if (std::fabs(denominator) > 0.0001f) // epsilon
  {
    t_prime = (numerator / denominator);
    if (t_prime >= min_t && t_prime < t)
    {
      t = t_prime;
      n = normal;
      return true;
    }
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
