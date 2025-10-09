#include "Types.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Engine.h"

namespace Krooz2D
{
		bool initWindow(int _width , int _height , string _title)
		{
			if(glfwInit() != GLFW_TRUE){
				glfwTerminate();
			}
			_Window = glfwCreateWindow(_width, _height, _title.c_str(), nullptr, nullptr);
			glfwMakeContextCurrent(static_cast<GLFWwindow*>(_Window));
			glfwWindowHint(GLFW_SAMPLES, 4);
			glfwSwapInterval(1);

			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
			glEnable(GL_MULTISAMPLE);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			return true;
		}

		void clearWindow(Vec3 color)
		{
			glfwPollEvents();
			glClearColor(color.x, color.y, color.z, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		GLFWwindow* GetWindowGlfw(){
			return static_cast<GLFWwindow*>(_Window);
		}

		bool isWindow(){
			return !glfwWindowShouldClose(static_cast<GLFWwindow*>(_Window));
		}

		void clearState()
		{
			glfwSwapBuffers(_Window);
		}

		void titleBarState(bool state)
		{
			glfwSetWindowAttrib(_Window,GLFW_DECORATED , state);
		}
} 

