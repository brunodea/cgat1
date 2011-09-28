#ifndef _CGA_T1_HEIGHT_MAP_H_
#define _CGA_T1_HEIGHT_MAP_H_

#include <string>
#include <vector>
#include "math/matrix_functions.hpp"
#include "glfw.h"

namespace util
{
    class HeightMap
    {
    public:
        HeightMap(const char *file_name, int max_altitude);
        ~HeightMap();

        void draw();
        void draw(int rowi, int coli, int rowf, int colf, int detail);
        void draw(int row, int col);

        void setMaxAltitude(int max_alt) { m_MaxAltitude = max_alt; }
        int maxAltitude() { return m_MaxAltitude; }
        
        void setGridSizes(int rows, int cols)
        {
            m_RowsNum = rows;
            m_ColsNum = cols;
        }
        void setRows(int rows) { m_RowsNum = rows; }
        int rows() { return m_RowsNum; }

        void setCols(int cols) { m_ColsNum = cols; }
        int cols() { return m_ColsNum; }

        void setFilename(std::string &filename) { m_filename = filename; }

        void setOffsets(float x, float y)
        {
            m_XOffset = x;
            m_YOffset = y;
        }

        std::vector<math::Vector3> *vertices() { return m_Vertices; }

        void detailUp()
        {
            m_DetailLevel *= 2;
            if(m_DetailLevel > m_ImageSize)
                m_DetailLevel = m_ImageSize;
        }

        void detailDown()
        {
            m_DetailLevel /= 2;
            if(m_DetailLevel < 2)
                m_DetailLevel = 2;
        }

    private:
        std::vector<math::Vector3> *vectors();

    private:
        std::string m_filename;
        int m_MaxAltitude;

        int m_ColsNum;
        int m_RowsNum;

        float m_XOffset;
        float m_YOffset;

        int m_DetailLevel;
        int m_ImageSize;

        GLFWimage m_Image;
        std::vector<math::Vector3> *m_Vertices;

    }; //end of class HeightMap.
} //end of namespace util.

#endif
