#include "Window.h"
#include <glad/glad.h>
#include <iostream>
#include <GLFW/glfw3.h>

Window::Window()
{
    Width_screen = 800;
    Height_screen = 600;
}
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
    
    glViewport(0,0,width,height);
}

int Window::CreateWindow()
{
    window = glfwCreateWindow(Width_screen, Height_screen,"CoursOpenGL",NULL,NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
}

