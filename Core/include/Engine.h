#pragma once
#include "memory"

struct  GLFWwindow;
class Engine{
    private:
    inline static GLFWwindow* mWindow = nullptr;
    inline static float mDeltaTime = 0.0f;

    void UpdateDeltaTime();

    public:
    bool Init(int width , int height , const char* title);
    bool IsValid();
    void BeginDraw(); 
    void EndDraw();
    
    static GLFWwindow* GetWindow(){ return mWindow; }
    static float GetDeltaTime(){ return mDeltaTime; }
};
