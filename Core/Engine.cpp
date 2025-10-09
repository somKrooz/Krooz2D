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

			gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

			return true;
		}

		void clearWindow()
		{
			glfwPollEvents();
			glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
		}

		GLFWwindow* GetWindowGlfw(){
			return static_cast<GLFWwindow*>(_Window);
		}

		bool isWindow(){
			return !glfwWindowShouldClose(static_cast<GLFWwindow*>(_Window));
		}
} 

