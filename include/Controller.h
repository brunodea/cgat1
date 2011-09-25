#ifndef _CGA_T1_CONTROLLER_H_
#define _CGA_T1_CONTROLLER_H_

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

    private:
        static Controller *m_sInstance;

        bool m_bRunning;

    }; //end of class Controller.
} //end of namespace CONTROL.

#endif