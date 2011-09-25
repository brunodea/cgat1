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
        HeightMap();
        HeightMap(std::string &file_name, int max_altitude, int min_altitude, int rows, int cols);

        std::vector<math::Vector3> *vectors();

        void setAltitudesLimit(int max_alt, int min_alt)
        {
            m_MaxAltitude = max_alt;
            m_MinAltitude = min_alt;
        }
        void setMaxAltitude(int max_alt) { m_MaxAltitude = max_alt; }
        int maxAltitude() { return m_MaxAltitude; }

        void setMinAltitude(int min_alt) { m_MinAltitude = min_alt; }
        int minAltitude() { return m_MinAltitude; }

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

    private:
        std::string m_filename;
        int m_MaxAltitude;
        int m_MinAltitude;

        int m_ColsNum;
        int m_RowsNum;

        GLFWimage *m_Image;

    }; //end of class HeightMap.
} //end of namespace util.

#endif
