#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Window
{
public:
    int Width_screen;
    int Height_screen;
    GLFWwindow* window;
    
    Window();

    void static framebufferSizeCallback(GLFWwindow* window, int width, int height);
    int CreateWindow();
};
