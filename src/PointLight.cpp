#include "PointLight.h"
#include <limits>
#include <iostream>

void PointLight::direction(
  const Eigen::Vector3d & q, Eigen::Vector3d & d, double & max_t) const
{
  ////////////////////////////////////////////////////////////////////////////
  d = (p - q) / (p - q).norm();
  if (d(0) != 0)
  {
    max_t = (p(0) - q(0)) / (double) d(0);
  }
  else 
  {
    max_t = std::numeric_limits<double>::infinity();
  }
  ////////////////////////////////////////////////////////////////////////////
}
