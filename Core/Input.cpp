#include "Input.h"
#include "Engine.h"

namespace Krooz2D
{
	bool Input::isHold(int Key)
	{
		return glfwGetKey(GetWindowGlfw(), Key) == GLFW_PRESS;
	}

	bool Input::isReleased(int Key)
	{
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
}
