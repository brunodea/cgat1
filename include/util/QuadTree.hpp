#ifndef _CGA_T1_QUADTREE_H_
#define _CGA_T1_QUADTREE_H_

#include "util/QuadNode.hpp"
#include "math/matrix_functions.hpp"
#include "glfw.h"
#include <vector>
#include "macros.h"
#include <iostream>
#include <cmath>

namespace util
{
    class QuadTree
    {
    public:
        QuadTree(std::vector<math::Vector3> *verts_matrix, int rows, int cols)
            : m_Detail(0)
        {
            m_Root = construct(verts_matrix, 0, rows-1, 0, cols-1, rows, cols);
            m_Height = adjustHeights(m_Root)-1;
        }
        ~QuadTree()
        {
            clear(m_Root);
        }

        void draw()
        {
            draw(m_Root);
        }

    private:
        QuadNode *construct(std::vector<math::Vector3> *verts_matrix, int row_init, int row_end, int col_init, int col_end, int rows, int cols)
        {
            QuadNode *res = NULL;

            if(col_end - col_init > 1 && row_end - row_init > 1)
            {
                res = new QuadNode();
                res->setVertices(verts_matrix->at((row_init*cols)+col_init), verts_matrix->at((row_init*cols)+col_end),
                                 verts_matrix->at((row_end*cols)+col_end), verts_matrix->at((row_end*cols)+col_init));
                res->setChild(construct(verts_matrix, row_init, (row_init+row_end)/2, col_init, (col_init+col_end)/2, rows, cols), QuadNode::NW);
                res->setChild(construct(verts_matrix, row_init, (row_init+row_end)/2, (col_init+col_end)/2, col_end, rows, cols), QuadNode::NE);
                res->setChild(construct(verts_matrix, (row_init+row_end)/2, row_end, (col_init+col_end)/2, col_end, rows, cols), QuadNode::SE);
                res->setChild(construct(verts_matrix, (row_init+row_end)/2, row_end, col_init, (col_init+col_end)/2, rows, cols), QuadNode::SW);
            }

            return res;
        }

        int adjustHeights(QuadNode *node)
        {
            if(node == NULL)
                return 0;
            int hnw = adjustHeights(node->nw())+1;
            int hne = adjustHeights(node->ne())+1;
            int hse = adjustHeights(node->se())+1;
            int hsw = adjustHeights(node->sw())+1;

            int height = std::max(std::max(hnw,hne),std::max(hse,hsw));
            node->setHeight(height-1);

            return height;
        }

        void draw(QuadNode *node)
        {
            if(node == NULL)
                return;

            QuadNode *nw = node->nw();
            if(nw != NULL)
                draw(nw);
            QuadNode *ne = node->ne();
            if(ne != NULL)
                draw(ne);
            QuadNode *se = node->se();
            if(se != NULL)
                draw(se);
            QuadNode *sw = node->sw();
            if(sw != NULL)
                draw(sw);
            
            if(node->height() == m_Detail)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glBegin(GL_TRIANGLES);
                    math::Vector3 hnw = node->verticeNW();
                    math::Vector3 hne = node->verticeNE();
                    math::Vector3 hse = node->verticeSE();
                    math::Vector3 hsw = node->verticeSW();

                    glColor4f(1.0,(hnw[1]+hsw[1]+hse[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);
                    glVertex3f(hsw[0],hsw[1],hsw[2]);
                    glVertex3f(hse[0],hse[1],hse[2]);

                    glColor4f(1.0,(hsw[1]+hse[1]+hne[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hse[0],hse[1],hse[2]);
                    glVertex3f(hne[0],hne[1],hne[2]);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);

                glEnd();
            }
        }

        void clear(QuadNode *node)
        {
            if(node == NULL)
                return;

            QuadNode *nw = node->nw();
            if(nw != NULL)
                clear(nw);
            QuadNode *ne = node->ne();
            if(ne != NULL)
                clear(ne);
            QuadNode *se = node->se();
            if(se != NULL)
                clear(se);
            QuadNode *sw = node->sw();
            if(sw != NULL)
                clear(sw);
            delete node;
        }

        void detailUp()
        {
        }

    private:
        QuadNode *m_Root;
        int m_Detail;
        int m_Height;
    }; //end of class QuadTree.
} //end of namespace util.

#endif