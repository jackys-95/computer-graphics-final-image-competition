#ifndef GET_TEXTURE_COLOUR_H
#define GET_TEXTURE_COLOUR_H
#include <Eigen/Core>
#include <vector>

Eigen::Vector3d get_texture_colour(const std::vector<unsigned char> &rgb, const int height, 
  const int width, const int offset);
  
#endif