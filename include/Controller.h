#ifndef _CGA_T1_CONTROLLER_H_
#define _CGA_T1_CONTROLLER_H_

#include "util/HeightMap.h"
#include "math/matrix_functions.hpp"
#include "Camera.hpp"
#include "util/QuadTree.hpp"

namespace CONTROL
{
    class Controller
    {
    public:
        ~Controller();
        static Controller *instance();

        void run();
        void onKeyPressed(int key, int state);

    private:
        Controller();

        void onRender();
        void onUpdate();
        
        void cameraOnKeyPress();
        void rotateCamera();

    private:
        static Controller *m_sInstance;

        bool m_bRunning;
        
        util::HeightMap *m_HeightMap;
        util::QuadTree *m_QuadTree;
        Camera m_FreeCamera;

    }; //end of class Controller.
} //end of namespace CONTROL.

#endif