#include "get_texture_colour.h"
#include <iostream>

Eigen::Vector3d get_texture_colour(const std::vector<unsigned char> &rgb, const int height, 
  const int width, const int offset)
{
  int new_height = 0;
  if (offset == 247)
  {
    new_height = 360 - height;
  }
  else
  {
    new_height = height;
  }
  int start_index = 3 * (width + 640 * new_height);
  return Eigen::Vector3d(rgb[0 + start_index],rgb[1 +start_index], rgb[2+start_index]);
}