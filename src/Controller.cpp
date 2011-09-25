#include "Controller.h"
#include "glfw.h"

using namespace CONTROL;

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true)
{
}

Controller::~Controller()
{
}

Controller *Controller::instance()
{
    if(m_sInstance == NULL)
        m_sInstance = new Controller();
    return m_sInstance;
}

void Controller::run()
{
    double last_render = 0;
    double last_update = 0;

    double frame_interval = 1.f/60.f;
    double update_interval = 1.f/90.f;

    double cur_time = 0;
    while(m_bRunning)
    {
        cur_time = glfwGetTime();
        if(cur_time - last_render > frame_interval) 
        {
            last_render = glfwGetTime();
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            onRender();
            glfwSwapBuffers();
        }
        if(cur_time - last_update > update_interval)
        {
            onUpdate();
            last_update = glfwGetTime();
        }
        glfwSleep(update_interval - (cur_time + glfwGetTime()));
    }
}

void Controller::onRender()
{
}


void Controller::onUpdate()
{
    m_bRunning = !glfwGetWindowParam(GLFW_OPENED) == 0;
    if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
        m_bRunning = false;
}

void Controller::onKeyPressed(int key, int state)
{
}
