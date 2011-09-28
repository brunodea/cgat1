#ifndef _CGA_T1_QUAD_BASE_HPP_
#define _CGA_T1_QUAD_BASE_HPP_

namespace util
{
    class QuadBase
    {
    public:
        QuadBase() {}
        
        virtual void render() = 0;
    protected:
    }; //end of class QuadBase.

} //end of namespace util.
#endif
