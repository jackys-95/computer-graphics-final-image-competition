#include "Sphere.h"
#include "Ray.h"
#include <cmath>

bool Sphere::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  // Check if discriminant indicates a solution:
  double A = ray.direction.dot(ray.direction);
  double B = ray.direction.dot(ray.origin - center);
  double discriminant = (B * B) - (A * ((ray.origin - center).dot(ray.origin - center) - (radius * radius)));

  double t_prime = 0;
  double t1 = 0;
  double t2 = 0;
  if (discriminant >= 0)
  {
    t1 = (-B + std::sqrt(discriminant)) / A;
    t2 = (-B - std::sqrt(discriminant)) / A;

    // Choose earlier t, because that is the first hit.
    if (t1 <= t2)
    {
      t_prime = t1;
    }
    else
    {
      t_prime = t2;
    }

    if (t_prime > min_t && t_prime < t)
    {
      t = t_prime;
      n = (ray.origin + (t * ray.direction) - center) / radius;
      return true;
    }
    else
    {
      return false;
    }
  }
  else
  {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}

