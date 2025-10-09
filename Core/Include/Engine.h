#pragma once
#include "Types.h"
#include "Default.h"
#include "GLFW/glfw3.h"  

namespace Krooz2D
{
    inline GLFWwindow* _Window = nullptr;  

    bool initWindow(int _width , int _height , std::string _title);
    void clearWindow(Vec3 Color);
    GLFWwindow* GetWindowGlfw();
		void clearState();
    bool isWindow();
		void titleBarState(bool state);
}
