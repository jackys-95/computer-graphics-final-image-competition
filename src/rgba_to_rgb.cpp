#include "rgba_to_rgb.h"

void rgba_to_rgb(
  const std::vector<unsigned char> & rgba,
  const int & width,
  const int & height,
  std::vector<unsigned char> & rgb)
{
  rgb.resize(height*width*3);
  ////////////////////////////////////////////////////////////////////////////
  // Add your code here
  int rgba_index = 0;
  for (int i = 0; i < height * width * 3; i += 3)
  {
  	rgb[i] = rgba[rgba_index];
  	rgb[i + 1] = rgba[rgba_index + 1];
  	rgb[i + 2] = rgba[rgba_index + 2];
  	rgba_index += 4;
  }
  ////////////////////////////////////////////////////////////////////////////
}
