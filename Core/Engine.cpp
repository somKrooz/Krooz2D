#include <Engine.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Maths.h"

float LastTime = 0.0f;


struct ColorTarget
{
    unsigned int fbo = 0;
    unsigned int tex = 0;

    ColorTarget(Vec2 size)
    {
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, size.x, size.y, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, tex, 0);
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
    }
};

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

    mTarget = new ColorTarget(Vec2(1280 , 720));
    post = new PostProcess();
        
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
    glBindFramebuffer(GL_FRAMEBUFFER, mTarget->fbo); // draw scene into texture
    glViewport(0, 0, 1280, 720);
    glClearColor(0.1f,0.1f,0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    UpdateDeltaTime();
}

void Engine::EndDraw(){
    glBindFramebuffer(GL_FRAMEBUFFER, 0); 
    post->Draw(mTarget->tex);

    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}
