#include "Input.h"
#include <GLFW/glfw3.h>

void Input::Init(GLFWwindow* window){
    s_Window = window;

}
bool Input::IsDown(int key){
    return glfwGetKey(s_Window, key) == GLFW_PRESS;
}

bool Input::IsJustPressed(int key){
    bool currentlyPressed = glfwGetKey(s_Window, key) == GLFW_PRESS;
    if (currentlyPressed && !keyStates[key]) {
        keyStates[key] = true;
        return true;
    }
    if (!currentlyPressed)
        keyStates[key] = false;

    return false;
}
