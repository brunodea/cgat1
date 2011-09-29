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

            adjustNeighbors(m_Root, m_Root->nw(), QuadNode::NW);
            adjustNeighbors(m_Root, m_Root->ne(), QuadNode::NE);
            adjustNeighbors(m_Root, m_Root->se(), QuadNode::SE);
            adjustNeighbors(m_Root, m_Root->sw(), QuadNode::SW);
        }
        ~QuadTree()
        {
            clear(m_Root);
        }

        void draw(const math::Vector3 &pos)
        {
            draw(m_Root, pos);
        }

        void detailDown()
        {
            m_Detail++;
            if(m_Detail > m_Height)
                m_Detail = m_Height;
        }
        void detailUp()
        {
            m_Detail--;
            if(m_Detail < 0)
                m_Detail = 0;
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
                QuadNode *nw = construct(verts_matrix, row_init, (row_init+row_end)/2, col_init, (col_init+col_end)/2, rows, cols);
                res->setChild(nw, QuadNode::NW);

                QuadNode *ne = construct(verts_matrix, row_init, (row_init+row_end)/2, (col_init+col_end)/2, col_end, rows, cols);
                res->setChild(ne, QuadNode::NE);

                QuadNode *se = construct(verts_matrix, (row_init+row_end)/2, row_end, (col_init+col_end)/2, col_end, rows, cols);
                res->setChild(se, QuadNode::SE);

                QuadNode *sw = construct(verts_matrix, (row_init+row_end)/2, row_end, col_init, (col_init+col_end)/2, rows, cols);
                res->setChild(sw, QuadNode::SW);
            }

            return res;
        }

        void adjustNeighbors(QuadNode *parent, QuadNode *node, QuadNode::DIR node_dir)
        {
            if(node == NULL)
                return;
            QuadNode *nw = node->nw();
            QuadNode *ne = node->ne();
            QuadNode *se = node->se();
            QuadNode *sw = node->sw();

            if(nw != NULL)
            {
                adjustNeighbors(node, nw, QuadNode::NW);
                adjustNeighbors(parent, node, nw, node_dir, QuadNode::NW);
            }
            if(ne != NULL)
            {
                adjustNeighbors(node, ne, QuadNode::NE);
                adjustNeighbors(parent, node, ne, node_dir, QuadNode::NE);
            }
            if(se != NULL)
            {
                adjustNeighbors(node, se, QuadNode::SE);
                adjustNeighbors(parent, node, se, node_dir, QuadNode::SE);
            }
            if(sw != NULL)
            {
                adjustNeighbors(node, sw, QuadNode::SW);
                adjustNeighbors(parent, node, sw, node_dir, QuadNode::SW);
            }
        }

        void adjustNeighbors(QuadNode *parent, QuadNode *node, QuadNode *target, QuadNode::DIR node_dir, QuadNode::DIR target_dir)
        {
            switch(node_dir)
            {
            case QuadNode::NW:
                adjustNeighborsNodeNW(parent, node, target, target_dir);
                break;
            case QuadNode::NE:
                adjustNeighborsNodeNE(parent, node, target, target_dir);
                break;
            case QuadNode::SE:
                adjustNeighborsNodeSE(parent, node, target, target_dir);
                break;
            case QuadNode::SW:
                adjustNeighborsNodeSW(parent, node, target, target_dir);
                break;
            default: break;
            }
        }

        void adjustNeighborsNodeNW(QuadNode *parent, QuadNode *node, QuadNode *target, QuadNode::DIR target_dir)
        {
            switch(target_dir)
            {
            case QuadNode::NW:
                target->setNeighbors(target, target, target, target);
                break;
            case QuadNode::NE:
                target->setNeighbors(target,target,node->nw(),node->sw());
                break;
            case QuadNode::SE: 
                target->setNeighbors(node->ne(),parent->ne()->nw(),node->sw(),parent->sw()->nw());
                break;
            case QuadNode::SW:
                target->setNeighbors(node->nw(),node->ne(),target,target);
                break;
            default: break;
            }
        }
         
        void adjustNeighborsNodeNE(QuadNode *parent, QuadNode *node, QuadNode *target, QuadNode::DIR target_dir)
        {
            switch(target_dir)
            {
            case QuadNode::NW:
                target->setNeighbors(target, target,parent->nw()->ne(), parent->nw()->se());
                break;
            case QuadNode::NE:
                target->setNeighbors(target,target,node->nw(),node->sw());
                break;
            case QuadNode::SE: 
                target->setNeighbors(node->ne(),target,node->sw(),parent->sw()->nw());
                break;
            case QuadNode::SW:
                target->setNeighbors(node->nw(),node->ne(),parent->nw()->sw(),parent->sw()->ne());
                break;
            default: break;
            }
        }

        void adjustNeighborsNodeSE(QuadNode *parent, QuadNode *node, QuadNode *target, QuadNode::DIR target_dir)
        {
            switch(target_dir)
            {
            case QuadNode::NW:
                target->setNeighbors(parent->ne()->sw(), parent->ne()->se(),parent->sw()->ne(), parent->sw()->se());
                break;
            case QuadNode::NE:
                target->setNeighbors(parent->ne()->se(),target,node->nw(),node->sw());
                break;
            case QuadNode::SE: 
                target->setNeighbors(node->ne(),target,node->sw(),target);
                break;
            case QuadNode::SW:
                target->setNeighbors(node->nw(),node->ne(),parent->sw()->se(),target);
                break;
            default: break;
            }
        }

        void adjustNeighborsNodeSW(QuadNode *parent, QuadNode *node, QuadNode *target, QuadNode::DIR target_dir)
        {
            switch(target_dir)
            {
            case QuadNode::NW:
                target->setNeighbors(parent->nw()->se(), parent->nw()->sw(),target, target);
                break;
            case QuadNode::NE:
                target->setNeighbors(parent->nw()->se(),parent->ne()->sw(),node->nw(),node->sw());
                break;
            case QuadNode::SE: 
                target->setNeighbors(node->ne(),parent->se()->nw(),node->sw(),target);
                break;
            case QuadNode::SW:
                target->setNeighbors(node->nw(),node->ne(),target,target);
                break;
            default: break;
            }
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

        void draw(QuadNode *node, const math::Vector3 &pos)
        {
            if(node == NULL)
                return;

            QuadNode *nw = node->nw();
            if(nw != NULL)
                draw(nw, pos);
            QuadNode *ne = node->ne();
            if(ne != NULL)
                draw(ne, pos);
            QuadNode *se = node->se();
            if(se != NULL)
                draw(se, pos);
            QuadNode *sw = node->sw();
            if(sw != NULL)
                draw(sw, pos);
            
            if(node->height() == m_Detail)
            {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                glBegin(GL_TRIANGLES);
                    math::Vector3 hnw = node->verticeNW();
                    math::Vector3 hne = node->verticeNE();
                    math::Vector3 hse = node->verticeSE();
                    math::Vector3 hsw = node->verticeSW();

                    math::Vector3 center = math::vector3f(std::min(hnw[0],hne[0])+(std::max(hnw[0],hne[0])-(std::min(hne[0],hnw[0])))/2.f, 
                                                          hnw[1],
                                                          std::min(hnw[2],hse[2])+(std::max(hnw[2],hse[2])-(std::min(hse[2],hnw[2])))/2.f);
                    //float distance = math::distance(center, pos);

                    //glColor4f(1.0,(hnw[1]+hsw[1]+hse[1])/(MAX_ALT*3),0.0,1.0);
                    //glVertex3f(hnw[0],hnw[1],hnw[2]);
                    //glVertex3f(hsw[0],hsw[1],hsw[2]);
                    //glVertex3f(hse[0],hse[1],hse[2]);

                    //glColor4f(1.0,(hsw[1]+hse[1]+hne[1])/(MAX_ALT*3),0.0,1.0);
                    //glVertex3f(hse[0],hse[1],hse[2]);
                    //glVertex3f(hne[0],hne[1],hne[2]);
                    //glVertex3f(hnw[0],hnw[1],hnw[2]);

                    //glColor4f(1.0,(hnw[1]+hsw[1]+hne[1])/(MAX_ALT*3),0.0,1.0);
                    //glVertex3f(hsw[0],hsw[1],hsw[2]);
                    //glVertex3f(hne[0],hne[1],hne[2]);
                    //glVertex3f(hse[0],hse[1],hse[2]);


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

                    glColor4f(1.0,(hnw[1]+center[1]+mu[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mu[0],mu[1],mu[2]);

                    glColor4f(1.0,(hne[1]+center[1]+mu[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hne[0],hne[1],hne[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mu[0],mu[1],mu[2]);

                    glColor4f(1.0,(hne[1]+center[1]+mr[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hne[0],hne[1],hne[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mr[0],mr[1],mr[2]);
                    
                    glColor4f(1.0,(hse[1]+center[1]+mr[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hse[0],hse[1],hse[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mr[0],mr[1],mr[2]);
                    
                    glColor4f(1.0,(hse[1]+center[1]+mb[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hse[0],hse[1],hse[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mb[0],mb[1],mb[2]);
                    
                    glColor4f(1.0,(hsw[1]+center[1]+mb[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hsw[0],hsw[1],hsw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(mb[0],mb[1],mb[2]);
                    
                    glColor4f(1.0,(hsw[1]+center[1]+ml[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hsw[0],hsw[1],hsw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(ml[0],ml[1],ml[2]);
                    
                    glColor4f(1.0,(hnw[1]+center[1]+ml[1])/(MAX_ALT*3),0.0,1.0);
                    glVertex3f(hnw[0],hnw[1],hnw[2]);
                    glVertex3f(center[0],center[1],center[2]);
                    glVertex3f(ml[0],ml[1],ml[2]);
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

    private:
        QuadNode *m_Root;
        int m_Detail;
        int m_Height;
    }; //end of class QuadTree.
} //end of namespace util.

#endif