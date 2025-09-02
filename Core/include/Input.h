#pragma once
struct GLFWwindow;

namespace KroozKeys
{
    constexpr int k_W = 87;
    constexpr int k_A = 65;
    constexpr int k_S = 83;
    constexpr int k_P = 80;
    constexpr int k_D = 68;
    constexpr int k_SPACE = 32;
} 


class Input {
private:
    inline static GLFWwindow* s_Window = nullptr;
    inline static bool keyStates[1024] = { false }; 
    
public:
    static void Init(GLFWwindow* window);
    static bool IsDown(int key);
    static bool IsJustPressed(int key);
};
