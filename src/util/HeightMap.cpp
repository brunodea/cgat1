#include "util/HeightMap.h"
#include "math/Vector.hpp"
#include <iostream>

using namespace util;

HeightMap::HeightMap()
    : m_filename("none"), m_MaxAltitude(0), m_MinAltitude(0), m_ColsNum(0), m_RowsNum(0), m_Image(NULL)
{}

HeightMap::HeightMap(std::string &filename, int max_altitude, int min_altitude, int rows, int cols)
    : m_filename(filename), m_MaxAltitude(max_altitude), m_MinAltitude(min_altitude), 
      m_ColsNum(cols), m_RowsNum(rows), m_Image(NULL)
{
}

std::vector<math::Vector3> *HeightMap::vectors()
{
    if(m_Image != NULL)
    {
        //nunca é para chegar até aqui.
        glfwFreeImage(m_Image);
    }

    std::vector<math::Vector3> *res = NULL;
    if(glfwReadImage(m_filename.c_str(), m_Image, -1) == GL_TRUE)
    {
        int w = m_Image->Width;
        int h = m_Image->Height;

        std::cout << "bytes per pixel: " << m_Image->BytesPerPixel << std::endl;

        glfwFreeImage(m_Image);
    }
    else
    {
        std::cout << "Height map " << m_filename.c_str() << " couldn't be loaded." << std::endl;
    }

    return res;
}
