#include "write_ppm.h"
#include <fstream>
#include <cassert>
#include <iostream>

bool write_ppm(
  const std::string & filename,
  const std::vector<unsigned char> & data,
  const int width,
  const int height,
  const int num_channels)
{
  ////////////////////////////////////////////////////////////////////////////
  // Replace with your code from computer-graphics-raster-images or email
  // jacobson@cs.toronto.edu for correct code.
  std::fstream fs;
  fs.open(filename, std::fstream::out);

  if (fs.is_open())
  {
    // write header
    fs << "P6\n" << width << ' ' << height << '\n' << 255 << '\n';

    // write image data
    if (num_channels == 1)
    {
      for (int i = height; i > -1; --i)
      {
        for (int j = 0; j < width; j++)
        {
          fs << data[(j + width * i)] << data[(j + width * i)] << data[(j + width * i)];
        }
      }
    }
    else
    {
      for (int i = height; i > -1; --i)
      {
        for (int j = 0; j < width; j++)
        {
          fs << data[0 + 3 *(j + width * i)] << data[1 + 3 *(j + width * i)] << data[2 + 3 *(j + width * i)];
        }
      }
    }

    fs.close();
    return true;
  }
  else 
  {
    std::cout << "Could not open file:" << filename << "for writing.";
  }
  
  return false;
  ////////////////////////////////////////////////////////////////////////////
}
