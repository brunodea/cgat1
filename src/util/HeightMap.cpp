#include "util/HeightMap.h"
#include "math/Vector.hpp"
#include <iostream>
#include <cstdlib>
#include "glfw.h"

using namespace util;

HeightMap::HeightMap(const char *filename, int max_altitude)
    : m_filename(filename), m_MaxAltitude(max_altitude), m_ColsNum(0), m_RowsNum(0), 
      m_XOffset(10), m_YOffset(10), m_DetailLevel(8), m_ImageSize(0)
{
    m_Vertices = vectors();
}

HeightMap::~HeightMap()
{
    delete m_Vertices;
}

void HeightMap::draw(int row, int col)
{
    /*bool c1 = false;
    for(int i = 0; i < m_RowsNum; i++)
    {
        int ydist = row-i;
        if(ydist < 0)
            ydist *= -1;
        for(int j = 0; j < m_ColsNum; j++)
        {
            int xdist = col-j;
            if(xdist < 0)
                xdist *= -1;
            if(xdist <= 4 && ydist <= 4)
            {
                draw(i-4,j-4,i,j+4,4);
                draw(i,j-4,i+4,j+4,4);
                c1 = true;
            }
        }
        if(c1)
            break;
    }*/
    draw();
    //draw(row-4,col-4,row+4,col+4,4);
    //draw(0,0,row-15,m_ColsNum,7);
    
//    draw(0,0,row-3,col-3,4);

    //draw(0,0,row-4,m_ColsNum-1,8);
    //draw(row+4,0,m_RowsNum-1,m_ColsNum-1,8);
    //draw(row-4,0,row+4,col-4,8);
    //draw(row-4,col+4,row+4,m_ColsNum,8);
}

void HeightMap::draw(int rowi, int coli, int rowf, int colf, int detail)
{
    if(m_Vertices->size() > 0)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glBegin(GL_TRIANGLES);

        for(int i = rowi; i <= rowf+detail; i += detail-1)
        {
            for(int j = coli; j <= colf+detail; j += detail-1)
            {
                if(j >= 0 && j < m_ColsNum-1 && i >= 0 && i < m_RowsNum-1)
                {
                    math::Vector3 v1 = m_Vertices->at((i*m_ColsNum)+j);
			        math::Vector3 v2 = m_Vertices->at(((i+detail-1)*m_ColsNum)+j);
			        math::Vector3 v3 = m_Vertices->at(((i+detail-1)*m_ColsNum)+j+detail-1);
			        math::Vector3 v4 = m_Vertices->at((i*m_ColsNum)+j+detail-1);
                
                    glColor4f(1.f,(v1[1]+v2[1]+v3[1])/(m_MaxAltitude*3),0.f,1.f);
                
                    glVertex3f(v1[0],v1[1],v1[2]);
			        glVertex3f(v2[0],v2[1],v2[2]);
			        glVertex3f(v3[0],v3[1],v3[2]);
                        
                    glColor4f(1.f,(v1[1]+v4[1]+v3[1])/(m_MaxAltitude*3),0.f,1.f);
                    glVertex3f(v1[0],v1[1],v1[2]);
                    glVertex3f(v4[0],v4[1],v4[2]);
			        glVertex3f(v3[0],v3[1],v3[2]);
                }
            }
        }
        glEnd();
    }
}

void HeightMap::draw()
{
    if(m_Vertices->size() > 0)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        
        glBegin(GL_TRIANGLES);
        for(int i = 0; i <= m_RowsNum-m_DetailLevel; i += m_DetailLevel-1)
        {
            for(int j = 0; j <= m_ColsNum-m_DetailLevel; j += m_DetailLevel-1)
            {
                math::Vector3 v1 = m_Vertices->at((i*m_ColsNum)+j);
			    math::Vector3 v2 = m_Vertices->at(((i+m_DetailLevel-1)*m_ColsNum)+j);
			    math::Vector3 v3 = m_Vertices->at(((i+m_DetailLevel-1)*m_ColsNum)+j+m_DetailLevel-1);
			    math::Vector3 v4 = m_Vertices->at((i*m_ColsNum)+j+m_DetailLevel-1);

                glColor4f(1.f,(v1[1]+v2[1]+v3[1])/(m_MaxAltitude*3),0.f,1.f);
                glVertex3f(v1[0],v1[1],v1[2]);
			    glVertex3f(v2[0],v2[1],v2[2]);
			    glVertex3f(v3[0],v3[1],v3[2]);
                        
                glColor4f(1.f,(v1[1]+v4[1]+v3[1])/(m_MaxAltitude*3),0.f,1.f);
                glVertex3f(v1[0],v1[1],v1[2]);
                glVertex3f(v4[0],v4[1],v4[2]);
			    glVertex3f(v3[0],v3[1],v3[2]);
            }
        }
        glEnd();
    }
}

std::vector<math::Vector3> *HeightMap::vectors()
{
    std::vector<math::Vector3> *res = new std::vector<math::Vector3>();
    if(glfwReadImage(m_filename.c_str(), &m_Image, GLFW_NO_RESCALE_BIT |  GLFW_ORIGIN_UL_BIT) == GL_TRUE)
    {
        m_ImageSize = m_Image.Width;
        m_ColsNum = m_Image.Width;
        m_RowsNum = m_Image.Height;
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