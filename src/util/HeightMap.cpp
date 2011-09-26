#include "util/HeightMap.h"
#include "math/Vector.hpp"
#include <iostream>
#include <cstdlib>

using namespace util;

HeightMap::HeightMap()
    : m_filename("none"), m_MaxAltitude(0), m_ColsNum(0), m_RowsNum(0), m_XOffset(10), m_YOffset(10)
{}

HeightMap::HeightMap(const char *filename, int max_altitude, int rows, int cols)
    : m_filename(filename), m_MaxAltitude(max_altitude), m_ColsNum(cols), m_RowsNum(rows), m_XOffset(10), m_YOffset(10)
{
}

std::vector<math::Vector3> *HeightMap::vectors()
{
    std::vector<math::Vector3> *res = new std::vector<math::Vector3>();
    if(glfwReadImage(m_filename.c_str(), &m_Image, GLFW_NO_RESCALE_BIT |  GLFW_ORIGIN_UL_BIT) == GL_TRUE)
    {
        float col_step = (float)m_Image.Width/m_ColsNum;
        float row_step = (float)m_Image.Height/m_RowsNum;
        int col = 0;
        int row = 0;

        while(row < m_RowsNum)
        {
            col = 0;
            while(col < m_ColsNum)
            {
                int v = (int)(row*row_step*m_Image.Width)+(int)col_step*col;
                v *= 4;

                unsigned char r = m_Image.Data[v];
                unsigned char g = m_Image.Data[v+1];
                unsigned char b = m_Image.Data[v+2];

                float val = r+g+b;
                int count = 1;
                if(v > 3)
                {
                    r = m_Image.Data[v-4];
                    g = m_Image.Data[v-3];
                    b = m_Image.Data[v-2];

                    val += r+g+b;
                    count++;
                }
                if(v < m_Image.Width*m_Image.Height)
                {
                    r = m_Image.Data[v+4];
                    g = m_Image.Data[v+5];
                    b = m_Image.Data[v+6];

                    val += r+g+b;                    
                    count++;
                }
                val /= count;

                float x = m_XOffset*col;
                float y = (val)*m_MaxAltitude/(255*3.f); //255+255+255.
                float z = m_YOffset*row;
                res->push_back(math::vector3f(x,y,z));

                col++;
            }
            row++;
        }
        
        glfwFreeImage(&m_Image);
    }
    else
    {
        std::cout << "Heightmap \"" << m_filename.c_str() << "\" couldn't be loaded." << std::endl;
    }

    return res;
}