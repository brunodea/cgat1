#ifndef _CGA_T1_QUAD_NODE_HPP_
#define _CGA_T1_QUAD_NODE_HPP_

#include <vector>
#include "math/matrix_functions.hpp"
#include "glfw.h"
#include <cmath>

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
        enum TRIANG //triangle
        {
            UP_LEFT_TRIANG = 0,
            UP_RIGHT_TRIANG,
            RIGHT_UP_TRIANG,
            RIGHT_BOTTOM_TRIANG,
            BOTTOM_RIGHT_TRIANG,
            BOTTOM_LEFT_TRIANG,
            LEFT_BOTTOM_TRIANG,
            LEFT_UP_TRIANG
        }; //end of enum TRING.
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
        
        void draw(TRIANG tr)
        {
            math::Vector3 hnw = verticeNW();
            math::Vector3 hne = verticeNE();
            math::Vector3 hse = verticeSE();
            math::Vector3 hsw = verticeSW();

            math::Vector3 center = math::vector3f(std::min(hnw[0],hne[0])+(std::max(hnw[0],hne[0])-(std::min(hne[0],hnw[0])))/2.f, 
                                                    hnw[1],
                                                    std::min(hnw[2],hse[2])+(std::max(hnw[2],hse[2])-(std::min(hse[2],hnw[2])))/2.f);
            math::Vector3 mu = math::vector3f(std::min(hnw[0],hne[0])+(std::max(hnw[0],hne[0])-(std::min(hne[0],hnw[0])))/2.f, 
                                                      hnw[1],
                                                      std::min(hnw[2],hne[2])+(std::max(hnw[2],hne[2])-(std::min(hne[2],hnw[2])))/2.f);

            math::Vector3 mr = math::vector3f(std::min(hse[0],hne[0])+(std::max(hse[0],hne[0])-(std::min(hne[0],hse[0])))/2.f, 
                                                hse[1],
                                                std::min(hse[2],hne[2])+(std::max(hse[2],hne[2])-(std::min(hne[2],hse[2])))/2.f);

            math::Vector3 mb = math::vector3f(std::min(hsw[0],hse[0])+(std::max(hsw[0],hse[0])-(std::min(hse[0],hsw[0])))/2.f, 
                                                hsw[1],
                                                std::min(hsw[2],hse[2])+(std::max(hsw[2],hse[2])-(std::min(hse[2],hsw[2])))/2.f);

            math::Vector3 ml = math::vector3f(std::min(hsw[0],hnw[0])+(std::max(hsw[0],hnw[0])-(std::min(hnw[0],hsw[0])))/2.f, 
                                                hsw[1],
                                                std::min(hsw[2],hnw[2])+(std::max(hsw[2],hnw[2])-(std::min(hnw[2],hsw[2])))/2.f);
            glBegin(GL_TRIANGLES);
                switch(tr)
                {
                case UP_LEFT_TRIANG:
                    glColor4f(1.0,(hnw[1]+center[1]+mu[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mu[0],mu[1],mu[2]);
                    break;
                case UP_RIGHT_TRIANG: 
                    glColor4f(1.0,(hne[1]+center[1]+mu[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hne[0],hne[1],hne[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mu[0],mu[1],mu[2]);
                    break;
                case RIGHT_UP_TRIANG:        
                    glColor4f(1.0,(hne[1]+center[1]+mr[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hne[0],hne[1],hne[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mr[0],mr[1],mr[2]);
                    break;
                case RIGHT_BOTTOM_TRIANG: 
                    glColor4f(1.0,(hse[1]+center[1]+mr[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hse[0],hse[1],hse[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mr[0],mr[1],mr[2]);
                    break;
                case BOTTOM_RIGHT_TRIANG:
                    glColor4f(1.0,(hse[1]+center[1]+mb[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hse[0],hse[1],hse[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mb[0],mb[1],mb[2]);
                    break;
                case BOTTOM_LEFT_TRIANG:
                    glColor4f(1.0,(hsw[1]+center[1]+mb[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hsw[0],hsw[1],hsw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mb[0],mb[1],mb[2]);
                    break;
                case LEFT_BOTTOM_TRIANG:
                    glColor4f(1.0,(hsw[1]+center[1]+ml[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hsw[0],hsw[1],hsw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(ml[0],ml[1],ml[2]);
                    break;
                case LEFT_UP_TRIANG:
                    glColor4f(1.0,(hnw[1]+center[1]+ml[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(ml[0],ml[1],ml[2]);
                    break;
                default: break;
                }
            glEnd();
        }

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
