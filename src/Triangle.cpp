#include "Triangle.h"
#include "Ray.h"
#include <Eigen/Geometry>

bool Triangle::intersect(
  const Ray & ray, const double min_t, double & t, Eigen::Vector3d & n) const
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code here
  double beta = 0;
  double gamma = 0;
  double t_prime = 0;

  // corners: a = corners[0], b = corners[1], c = corners[2]
  // Calculate dummy variables for Cramer's rule calculation (from textbook)
  double a = std::get<0>(corners)(0) - std::get<1>(corners)(0);
  double d = std::get<0>(corners)(0) - std::get<2>(corners)(0);
  double g = ray.direction(0);

  double b = std::get<0>(corners)(1) - std::get<1>(corners)(1);
  double e = std::get<0>(corners)(1) - std::get<2>(corners)(1);
  double h = ray.direction(1);

  double c = std::get<0>(corners)(2) - std::get<1>(corners)(2);
  double f = std::get<0>(corners)(2) - std::get<2>(corners)(2);
  double i = ray.direction(2);

  double j = std::get<0>(corners)(0) - ray.origin(0);
  double k = std::get<0>(corners)(1) - ray.origin(1);
  double l = std::get<0>(corners)(2) - ray.origin(2);

  // intermediate dummy variables for calculating beta, gamma, and t
  double ei_minus_hf = (e * i) - (h * f);
  double gf_minus_di = (g * f) - (d * i);
  double dh_minus_eg = (d * h) - (e * g);
  double ak_minus_jb = (a * k) - (j * b);
  double jc_minus_al = (j * c) - (a * l);
  double bl_minus_kc = (b * l) - (k * c);

  double M = (a * ei_minus_hf) + (b * gf_minus_di) + (c * dh_minus_eg);
  t_prime = -(((f * ak_minus_jb) + (e * jc_minus_al) + (d * bl_minus_kc)) / M);

  if (t_prime < min_t)
  {
    return false;
  }

  gamma = ((i * ak_minus_jb) + (h * jc_minus_al) + (g * bl_minus_kc)) / M;
  if (gamma < 0 || gamma > 1)
  {
    return false;
  }

  beta = ((j * ei_minus_hf) + (k * gf_minus_di) + (l * dh_minus_eg)) / M;
  if (beta < 0 || beta > (1 - gamma))
  {
    return false;
  }

  if (t_prime < t)
  {
    t = t_prime;
    // given two vectors u and v, the cross product (u X v) = n (normal vector)
    // u = b - a, v = c - a
    Eigen::Vector3d u = std::get<1>(corners) - std::get<0>(corners);
    Eigen::Vector3d v = std::get<2>(corners) - std::get<0>(corners);
    n = u.cross(v);
    n.normalize();

    return true;
  }
  else
  {
    return false;
  }
  ////////////////////////////////////////////////////////////////////////////
}


