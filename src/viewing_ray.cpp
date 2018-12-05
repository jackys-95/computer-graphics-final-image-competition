#include "viewing_ray.h"

void viewing_ray(
  const Camera & camera,
  const int i,
  const int j,
  const int width,
  const int height,
  Ray & ray)
{
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  // Image bounds
  double l = -((double) (camera.width / 2));
  double r = -l;
  double b = -((double) (camera.height / 2));
  double t = -b;

  // Calculate pixel position on image plane (u, v).
  double image_u = (l + (r - l) * (j + 0.5) / width);
  double image_v = (b + (t - b) * (i + 0.5) / height);

  ray.origin = camera.e;
  ray.direction = -(camera.d * camera.w) + (image_u * camera.u) + (image_v * camera.v);
  ////////////////////////////////////////////////////////////////////////////
}
