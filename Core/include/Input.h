#pragma once
struct GLFWwindow;
class Input {
private:
    inline static GLFWwindow* s_Window = nullptr;
    inline static bool keyStates[1024] = { false }; 

public:
    static void Init(GLFWwindow* window);
    static bool IsDown(int key);
    static bool IsJustPressed(int key);
};
