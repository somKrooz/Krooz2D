#pragma once
#include "Types.h"
#include "GLFW/glfw3.h"  

namespace Krooz2D
{
    inline GLFWwindow* _Window = nullptr;  

    bool initWindow(int _width , int _height , std::string _title);
    void clearWindow();
    GLFWwindow* GetWindowGlfw();
    bool isWindow();
}
