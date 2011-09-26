#include "Controller.h"
#include "glfw.h"
#include <vector>
#include "math/matrix_functions.hpp"

using namespace CONTROL;

#define MAX_ALT 300.f

Controller *Controller::m_sInstance = NULL;

Controller::Controller()
    : m_bRunning(true), m_Cols(100), m_Rows(100),
    m_FreeCamera(math::vector3f(0,200,300),math::vector3f(300,0,0),math::vector3f(0,1,0))
{
    util::HeightMap h(util::HeightMap("resources/h.tga",MAX_ALT,m_Cols,m_Rows));
    h.setOffsets(30,30);
    m_HeightMapVectors = h.vectors();
    m_FreeCamera.setSpeed(5.f);
}

Controller::~Controller()
{
    delete m_HeightMapVectors;
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
    math::Vector3 eye = m_FreeCamera.eye();
    math::Vector3 target = m_FreeCamera.target();
    math::Vector3 up = m_FreeCamera.up();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //rotateCamera();
    gluLookAt(eye[0],eye[1],eye[2], target[0],target[1],target[2], up[0],up[1],up[2]);

    if(m_HeightMapVectors->size() > 0)
    {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glScalef(.3,.3,.3);
		int yspacing = 3;
		int xspacing = 3;
        for(int i = 0; i < m_Rows-1; i += yspacing)
        {
            glBegin(GL_TRIANGLES);
                    for(int j = 0; j < m_Cols-1; j += xspacing)
                    {
                        math::Vector3 v1 = m_HeightMapVectors->at((i*m_Cols)+j);
						math::Vector3 v2 = m_HeightMapVectors->at(((i+yspacing)*m_Cols)+j);
						math::Vector3 v3 = m_HeightMapVectors->at(((i+yspacing)*m_Cols)+j+xspacing);
						math::Vector3 v4 = m_HeightMapVectors->at((i*m_Cols)+j+xspacing);
                        glColor4f(1.f,v1[1]/MAX_ALT,0.f,1.f);
                        glVertex3f(v1[0],v1[1],v1[2]);
						glVertex3f(v2[0],v2[1],v2[2]);
						glVertex3f(v3[0],v3[1],v3[2]);

                        glVertex3f(v1[0],v1[1],v1[2]);
                        glVertex3f(v4[0],v4[1],v4[2]);
						glVertex3f(v3[0],v3[1],v3[2]);
                    }
            glEnd();
        }
    }
}


void Controller::onUpdate()
{
    m_bRunning = !glfwGetWindowParam(GLFW_OPENED) == 0;
    if(glfwGetKey(GLFW_KEY_ESC) == GLFW_PRESS)
        m_bRunning = false;
    
    cameraOnKeyPress();
    m_FreeCamera.setTarget(m_FreeCamera.direction()+m_FreeCamera.eye());
}

void Controller::onKeyPressed(int key, int state)
{
}

void Controller::cameraOnKeyPress()
{
    if(glfwGetKey('S') == GLFW_PRESS)
        m_FreeCamera.moveBackwards();
    else if(glfwGetKey('W') == GLFW_PRESS)
        m_FreeCamera.moveForward();

    if(glfwGetKey('A') == GLFW_PRESS)
        m_FreeCamera.moveLeft();
    else if(glfwGetKey('D') == GLFW_PRESS)
        m_FreeCamera.moveRight();

    if(glfwGetKey('Z') == GLFW_PRESS)
        m_FreeCamera.moveUp();
    else if(glfwGetKey('X') == GLFW_PRESS)
        m_FreeCamera.moveDown();
}

//com rotacao para a camera fica mto ruim de mexer.
void Controller::rotateCamera()
{
    float roll = math::radToDegree(m_FreeCamera.getRollAngle());
    float yaw = math::radToDegree(m_FreeCamera.getYawAngle());
    float pitch = math::radToDegree(m_FreeCamera.getPitchAngle());
    
    float angle = (float)PI/20.f;
    if(glfwGetKey('U') == GLFW_PRESS)
        m_FreeCamera.rotate(angle,0.f,0.f);
    else if(glfwGetKey('O') == GLFW_PRESS)
        m_FreeCamera.rotate(-angle,0.f,0.f);

    if(glfwGetKey('L') == GLFW_PRESS)
        m_FreeCamera.rotate(0.f,angle,0.f);
    else if(glfwGetKey('J') == GLFW_PRESS)
        m_FreeCamera.rotate(0.f,-angle,0.f);

    if(glfwGetKey('I') == GLFW_PRESS)
        m_FreeCamera.rotate(0.f,0.f,angle);
    else if(glfwGetKey('K') == GLFW_PRESS)
        m_FreeCamera.rotate(0.f,0.f,-angle);

    glRotatef(roll ,1.f,0.f,0.f);
    glRotatef(yaw  ,0.f,1.f,0.f);
    glRotatef(pitch,0.f,0.f,1.f);
}