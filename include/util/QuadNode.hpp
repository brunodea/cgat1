#ifndef _CGA_T1_QUAD_NODE_HPP_
#define _CGA_T1_QUAD_NODE_HPP_

#include <vector>
#include "math/matrix_functions.hpp"

namespace util
{
    class QuadNode
    {
    public:
        enum DIR //direction.
        {
            NW = 0,
            NE,
            SE,
            SW,
        }; //end of enum DIR.
        enum NEIGHBOR
        {
            UP = 0,
            UP_RIGHT,
            LEFT,
            LEFT_BOTTOM
        }; //end of enum NEIGHBOR.
        enum RES //resolutions
        {
            R1 = 0,
            R2,
            R3,
            R4
        };
    public:
        QuadNode() : m_Height(0) { init(); }

        void setChild(QuadNode *child, DIR d) { m_Children[d] = child; }
        void setChildren(QuadNode *nw, QuadNode *ne, QuadNode *se, QuadNode *sw)
        {
            setChild(nw, NW);
            setChild(ne, NE);
            setChild(se, SE);
            setChild(sw, SW);
        }
        QuadNode *child(DIR d) { return m_Children[d]; }
        QuadNode *nw() { return m_Children[NW]; }
        QuadNode *ne() { return m_Children[NE]; }
        QuadNode *se() { return m_Children[SE]; }
        QuadNode *sw() { return m_Children[SW]; }

        void setVertice(math::Vector3 height, DIR d) { m_VerticesCorners[d] = height; }
        void setVertices(math::Vector3 h_nw, math::Vector3 h_ne, math::Vector3 h_se, math::Vector3 h_sw)
        {
            setVertice(h_nw, NW);
            setVertice(h_ne, NE);
            setVertice(h_se, SE);
            setVertice(h_sw, SW);
        }
        math::Vector3 vertice(DIR d) { return m_VerticesCorners[d]; }
        math::Vector3 verticeNW() { return m_VerticesCorners[NW]; }
        math::Vector3 verticeNE() { return m_VerticesCorners[NE]; }
        math::Vector3 verticeSE() { return m_VerticesCorners[SE]; }
        math::Vector3 verticeSW() { return m_VerticesCorners[SW]; }

        void setNeighbor(QuadNode *neighbor, NEIGHBOR n) { m_Neighbors[n] = neighbor; }
        void setNeighbors(QuadNode *up, QuadNode *up_right, QuadNode *left, QuadNode *left_bottom)
        {
            setNeighbor(up, UP);
            setNeighbor(up_right, UP_RIGHT);
            setNeighbor(left, LEFT);
            setNeighbor(left_bottom, LEFT_BOTTOM);
        }
        QuadNode *neighbor(NEIGHBOR n) { return m_Neighbors[n]; }
        QuadNode *neighborUp() { return m_Neighbors[UP]; }
        QuadNode *neighborUpRight() { return m_Neighbors[UP_RIGHT]; }
        QuadNode *neighborLeft() { return m_Neighbors[LEFT]; }
        QuadNode *neighborLeftBottom() { return m_Neighbors[LEFT_BOTTOM]; }

        int resolution(RES r) { return m_Resolutions[r]; }
        void setResolution(int val, RES r) { m_Resolutions[r] = val; }

        void setHeight(int height) { m_Height = height; }
        int height() { return m_Height; }
    private:
        void init()
        {
            for(int i = 0; i < 4; i++)
            {
                m_Children[i] = 0;
                m_VerticesCorners[i] = math::vector3f(0,0,0);
                m_Neighbors[i] = 0;
                m_Resolutions[i] = 0;
            }
        }
    private:
        QuadNode *m_Children[4];
        math::Vector3 m_VerticesCorners[4];
        QuadNode *m_Neighbors[4];
        int m_Resolutions[4];
        int m_Height;
    };
} //end of namespace util.
#endif
