//#ifndef _CGA_T1_QUADTREE_H_
//#define _CGA_T1_QUADTREE_H_
//
//namespace util
//{
//    /*
//    class QuadBase;
//    class QuadNode;
//    class QuadRegion;
//    */
//    enum Direction
//    {
//        NE = 0,
//        SE,
//        SW,
//        NW
//    }; //end of enum Direction.
//    
//    enum Neighbor
//    {
//        UPPER = 0,
//        UPPER_RIGHT,
//        LEFT,
//        LOWER_LEFT
//    }; //end of enum Neighbor.
//
//    enum Resolution
//    {
//        R1 = 0,
//        R2,
//        R3,
//        R4
//    }; //end of enum Resolution.
//
//    class QuadBase
//    {
//    public:
//        QuadBase() {}
//        
//        virtual void render() = 0;
//    protected:
//    }; //end of class QuadBase.
//
//    
//    class QuadRegion : public QuadBase
//    {
//    public:
//        QuadRegion()
//        {
//            for(int i = 0; i < 4; i++)
//            {
//                m_Neighbors[i] = 0;
//                m_Resolutions[i] = 0;
//            }
//        }
//
//        QuadRegion(QuadBase *upper, QuadBase *upper_right, QuadBase *left, QuadBase *lower_left)
//        {
//            m_Neighbors[UPPER] = upper;
//            m_Neighbors[UPPER_RIGHT] = upper_right;
//            m_Neighbors[LEFT] = left;
//            m_Neighbors[LOWER_LEFT] = lower_left;
//
//            for(int i = 0; i < 4; i++)
//            {
//                m_Resolutions[i] = 0;
//            }
//        }
//
//        QuadBase *neighbor(Neighbor n) { m_Neighbors[n]; }
//
//        int resolution(Resolution r) { m_Resolutions[r]; }
//        void setResolution(int value, Resolution r) { m_Resolutions[r] = value; }
//
//        void render()
//        {
//        }
//
//    private:
//        QuadBase *m_Neighbors[4];
//        int m_Resolutions[4];
//
//    }; //end of class QuadRegion.
//
//    class QuadNode : public QuadBase
//    {
//    public:
//        QuadNode()
//        {
//            for(int i = 0; i < 4; i++)
//            {
//                m_vpChildren[i] = 0;
//                m_vCornersHeight[i] = 0;
//            }
//        }
//
//        QuadNode(QuadNode *ne, QuadNode *se, QuadNode *sw, QuadNode *nw)
//        {
//            m_vpChildren[0] = ne;
//            m_vpChildren[1] = se;
//            m_vpChildren[2] = sw;
//            m_vpChildren[3] = nw;
//
//            for(int i = 0; i < 4; i++)
//                m_vCornersHeight[i] = 0;
//        }
//
//        QuadNode *child(Direction dir) { return m_vpChildren[dir]; }
//
//        int cornerHeight(Direction dir) { return m_vCornersHeight[dir]; }
//        void setCornerHeight(int height, Direction dir) { m_vCornersHeight[dir] = height; }
//
//        void render()
//        {
//        }
//
//    private:
//        QuadNode *m_vpChildren[4];
//        int m_vCornersHeight[4];
//    };
//
//    class QuadTree
//    {
//    public:
//        QuadTree()
//            : m_Root(0)
//        {}
//
//        QuadTree(QuadBase *root)
//            : m_Root(root)
//        {}
//
//        QuadBase *root() { return m_Root; }
//
//    private:
//        QuadBase *m_Root;
//
//    }; //end of class QuadTree.
//} //end of namespace util.
//
//#endif