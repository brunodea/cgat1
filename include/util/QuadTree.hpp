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
            : m_Detail(3225), m_bWireframe(true)
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
            draw(m_Root, pos, m_Root->height(), m_Detail);
        }

        void detailDown()
        {
            m_Detail -= 25;
            if(m_Detail < 0)
                m_Detail = 0;
        }
        void detailUp()
        {
            m_Detail += 25;
            if(m_Detail > 100000)
                m_Detail = 100000;
        }
        void toggleWireframe() { m_bWireframe = !m_bWireframe; }


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

        /*float computeError(QuadNode *node)
        {
            float errRight = 0, errBottom = 0, errCenter = 0, err = 0;
            float filhos;
            float maxi = 0, mini = 0, delta = 0;

            QuadNode *nw = node->nw();
            QuadNode *ne = node->ne();
            QuadNode *se = node->se();
            QuadNode *sw = node->sw();

            if(nw != NULL)
            {
                delta = (node->verticeNW()[1]+node->verticeSE()[1])/2.0;
                maxi = std::max(delta, nw->verticeSE()[1]);
                mini = std::max(delta, nw->verticeSE()[1]);
                errRight = (mini > 1) ? (maxi/mini
            }

        }*/

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

        bool draw(QuadNode *node, const math::Vector3 &pos, int detail, float min_dist)
        {
            if(node == NULL)
                return true;
            math::Vector3 hnw = node->verticeNW();
            math::Vector3 hne = node->verticeNE();
            math::Vector3 hse = node->verticeSE();
            math::Vector3 hsw = node->verticeSW();

            bool rendernw = true;
            bool renderne = true;
            bool renderse = true;
            bool rendersw = true;
            if(node->height() > 0)
            {
                float c = 0.8;
                QuadNode *nw = node->nw();
                if(nw != NULL)
                {
                    float dnw = math::distance(math::vector3f(hnw[0],0,hnw[2]), pos);
                    if(dnw <= min_dist)
                        rendernw = draw(nw, pos,nw->height(), min_dist*c);
                }
                QuadNode *ne = node->ne();
                if(ne != NULL)
                {
                    float dne = math::distance(math::vector3f(hne[0],0,hne[2]), pos);
                    if(dne <= min_dist)
                        renderne = draw(ne, pos, ne->height(), min_dist*c);
                }
                QuadNode *se = node->se();
                if(se != NULL)
                {
                    float dse = math::distance(math::vector3f(hse[0],0,hse[2]), pos);
                    if(dse <= min_dist)
                        renderse = draw(se, pos, se->height(), min_dist*c);
                }
                QuadNode *sw = node->sw();
                if(sw != NULL)
                {
                    float dsw = math::distance(math::vector3f(hsw[0],0,hsw[2]), pos);
                    if(dsw <= min_dist)
                        rendersw = draw(sw, pos, sw->height(), min_dist*c);
                }
            }
            if(m_bWireframe == true)
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            else
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            
            if(rendernw)
            {
                node->draw(QuadNode::UP_LEFT_TRIANG);
                node->draw(QuadNode::LEFT_UP_TRIANG);
            }
            if(renderne)
            {
                node->draw(QuadNode::UP_RIGHT_TRIANG);
                node->draw(QuadNode::RIGHT_UP_TRIANG);
            }
            if(renderse)
            {
                node->draw(QuadNode::RIGHT_BOTTOM_TRIANG);
                node->draw(QuadNode::BOTTOM_RIGHT_TRIANG);
            }
            if(rendersw)
            {
                node->draw(QuadNode::BOTTOM_LEFT_TRIANG);
                node->draw(QuadNode::LEFT_BOTTOM_TRIANG);
            }
            return false;
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
        bool m_bWireframe;
    }; //end of class QuadTree.
} //end of namespace util.

#endif