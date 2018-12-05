#include "first_hit.h"
#include <cfloat>

bool first_hit(
  const Ray & ray, 
  const double min_t,
  const std::vector< std::shared_ptr<Object> > & objects,
  int & hit_id, 
  double & t,
  Eigen::Vector3d & n)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  double t_prime = DBL_MAX;
  int t_prime_index = -1;

  for (int i = 0; i < objects.size(); i++)
  {    
    // This will only be true if it has found a closer hit to the eye
    if (objects[i]->intersect(ray, min_t, t_prime, n))
    {
      t_prime_index = i;
    }
  }

  if (t_prime_index != -1)
  {
    hit_id = t_prime_index;
    t = t_prime;
    return true;
  }

  return false;
  ////////////////////////////////////////////////////////////////////////////
}
