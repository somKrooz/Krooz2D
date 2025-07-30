#include <Engine.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

float LastTime = 0.0f;

bool Engine::Init(int width , int height , const char* title){
    if(glfwInit() != GLFW_TRUE){
        glfwDestroyWindow(mWindow);
        glfwTerminate();
        return false;
    }
    mWindow  = glfwCreateWindow(width , height , title , nullptr,nullptr);
    glfwMakeContextCurrent(mWindow);
    glfwSetWindowAttrib(mWindow, GLFW_RESIZABLE, GLFW_FALSE);

    
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        glfwTerminate();
        return false;
    }

        
    glEnable(GL_MULTISAMPLE);
    glfwWindowHint(GLFW_SAMPLES, 4);

    return true;
}

void Engine::UpdateDeltaTime(){
    float currentTime = static_cast<float>(glfwGetTime());
    mDeltaTime = currentTime - LastTime;
    LastTime = currentTime;
}

bool Engine::IsValid(){
    return mWindow && !glfwWindowShouldClose(mWindow);
}

void Engine::BeginDraw(){
    glClearColor(0.1f,0.1f,0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UpdateDeltaTime();
}

void Engine::EndDraw(){
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}
