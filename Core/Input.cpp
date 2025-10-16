#include "Input.h"
#include "Engine.h"
#include "algorithm"


double Scroll_Delta = 0.0f;
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    Scroll_Delta += yoffset * 0.1f; 
		Scroll_Delta = std::clamp(static_cast<float>(Scroll_Delta) , 0.1f , 10.0f);
}
namespace Krooz2D
{
	Input::Input()
	{
		glfwSetScrollCallback(_Window , scroll_callback);
	}
	bool Input::isHold(int Key)
	{
		if(isLocked) return false;
		return glfwGetKey(GetWindowGlfw(), Key) == GLFW_PRESS;
	}

	bool Input::isReleased(int Key)
	{
		if(isLocked) return false;
		return glfwGetKey(GetWindowGlfw(), Key) == GLFW_RELEASE;
	}
	bool Input::isJustPressed(int Key)
	{
		bool currentlyPressed = glfwGetKey(GetWindowGlfw(), Key) == GLFW_PRESS;
		if(currentlyPressed && !keyStates[Key])
		{
			keyStates[Key] = true;
			return true;
		}
			if (!currentlyPressed)
				keyStates[Key] = false;

		 return false;
	}

	void Input::GetCursorLocation(Vec2& loc)
	{
		double xpos, ypos;	
		glfwGetCursorPos(_Window ,&xpos , &ypos);

		loc.x = xpos;
		loc.y = ypos;
	}

	void Input::GetScrollValue(float& val){
		val = static_cast<float>(Scroll_Delta);
	}
}
