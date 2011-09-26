#include "util/HeightMap.h"
#include "math/Vector.hpp"
#include <iostream>
#include <cstdlib>

using namespace util;

HeightMap::HeightMap()
    : m_filename("none"), m_MaxAltitude(0), m_ColsNum(0), m_RowsNum(0)
{}

HeightMap::HeightMap(const char *filename, int max_altitude, int rows, int cols)
    : m_filename(filename), m_MaxAltitude(max_altitude), m_ColsNum(cols), m_RowsNum(rows)
{
}

std::vector<math::Vector3> *HeightMap::vectors()
{
    std::vector<math::Vector3> *res = new std::vector<math::Vector3>();
    if(glfwReadImage(m_filename.c_str(), &m_Image, GLFW_NO_RESCALE_BIT |  GLFW_ORIGIN_UL_BIT) == GL_TRUE)
    {
        //std::cout << "bytes per pixel: " << m_Image.BytesPerPixel << std::endl;

        float col_step = (float)m_Image.Width/m_ColsNum;
        float row_step = (float)m_Image.Height/m_RowsNum;
        int col = 0;
        int row = 0;

        std::cout << "row_step: " << row_step << " col_step: " << col_step << std::endl;
        std::cout << "Width: " << m_Image.Width << " Height: " << m_Image.Height << std::endl;
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
                //int a = m_Image.Data[v+3];
                
                //std::cout << v << " ";
                //if(r!=0||g!=0||b!=0)
                //std::cout << "(" << r << "," << g << "," << b << "," << a << ") ";

                float x = 10*col;
                float y = (r+g+b)*m_MaxAltitude/(255*3.f); //255+255+255.
                float z = 10*row;

                //std::cout << y << " ";

                res->push_back(math::vector3f(x,y,z));

                col++;
            }
            //std::cout << std::endl;
            row++;
        }


        //for(int i = 0; i < m_Image.Height; i += 1)
        //{
        //    col = 0;
        //    for(int j = 0; j < m_Image.Width; j += m_Image.BytesPerPixel)
        //    {
        //        int r = m_Image.Data[(i*m_Image.Width)+j];
        //        int g = m_Image.Data[(i*m_Image.Width)+j+1];
        //        int b = m_Image.Data[(i*m_Image.Width)+j+2];
        //        int a = m_Image.Data[(i*m_Image.Width)+j+2];
        //        
        //        float x = 50*col;
        //        float y = (r+g+b)*m_MaxAltitude/765.f; //255+255+255.
        //        float z = 50*row;

        //        res->push_back(math::vector3f(x,y,z));

        //        col++;
        //    }
        //    row++;
        //}

        glfwFreeImage(&m_Image);
    }
    else
    {
        std::cout << "Heightmap \"" << m_filename.c_str() << "\" couldn't be loaded." << std::endl;
    }

    return res;
}