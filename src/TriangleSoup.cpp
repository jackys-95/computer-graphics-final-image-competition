#include "TriangleSoup.h"
#include "Ray.h"
// Hint
#include "first_hit.h"

bool TriangleSoup::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here:
  int hit_id;
  double t_prime;
  if (first_hit(ray, min_t, triangles, hit_id, t_prime, n))
  {
    t = t_prime;
    return true;
  }
  return false;
  ////////////////////////////////////////////////////////////////////////////
}



