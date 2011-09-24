#include "glfw.h"
#include <cstdlib>
#include <iostream>

#include "macros.h"

void initWindowStuff()
{
    if(!glfwInit())
        exit(EXIT_FAILURE);

    if(!glfwOpenWindow(WINDOW_WIDTH, WINDOW_HEIGHT, 8, 8, 8, 8, 8, 8, GLFW_WINDOW))
    {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
}

void GLFWCALL onKeyPressed(int key, int state)
{
}

void GLFWCALL handleResize(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    gluPerspective(45.f, (float)width/(float)height, 0.1, 1000);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void setCallbacks()
{
    glfwSetKeyCallback(onKeyPressed);
    glfwSetWindowSizeCallback(handleResize);
}

void initOpenGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.7f,0.7f,1.f,1.f);
}

void cleanUp()
{
    glfwTerminate();
}

int main()
{
    initWindowStuff();
    setCallbacks();
    initOpenGL();
    handleResize(WINDOW_WIDTH, WINDOW_HEIGHT);

    cleanUp();
    exit(EXIT_SUCCESS);
}
