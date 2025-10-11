#include "Input.h"
#include "Engine.h"
#include "algorithm"

namespace Krooz2D
{
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
}
