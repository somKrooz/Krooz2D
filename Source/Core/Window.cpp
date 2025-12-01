#define RGFW_IMPLEMENTATION
#define RGFW_OPENGL
#include "RGFW.h"
#include "Core/Texture.h"
#include "Core/Window.h"   
#include "Core/Buffer.h"   
#include "Core/input.h"
#include "Utility/Logs.h"
#include "glad/glad.h"
#include "chrono"

RGFW_window* _window = nullptr;
RGFW_event _Event;


void createWindow(int width , int height , string title)
{
	_window = RGFW_createWindow(title.c_str() , 0, 0, width, height, RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowOpenGL);
	_size = Vec2(width , height);
	if(_window == nullptr){
		Error("Window | Opengl Context Creation Failed...");
		return;
	}
	gladLoadGLLoader((GLADloadproc)RGFW_getProcAddress_OpenGL);
}

void setTileName(string newName){
	RGFW_window_setName(getWindow() , newName.c_str());
}

void setWindowOpacity(int value){
	if(value < 0 || value > 255) return;
	RGFW_window_setOpacity(getWindow() , 100);
}

void setCursor(bool value){
	RGFW_window_showMouse(getWindow(),value);
}

void setDecorator(bool value){
	RGFW_window_setBorder(getWindow() , value);
}

void getInfo(){

	const char* version = reinterpret_cast<const char*>(glGetString(GL_VERSION));

	GLint maxTextureSize;
	glGetIntegerv(GL_MAX_TEXTURE_IMAGE_UNITS, &maxTextureSize);


	Warn("Krooz2D version ( 0.1.2 ) : Som Krooz");
	Log("Opengl Version: {}" , version);
	Log("GPU max Texture Limit: {}" , maxTextureSize);
	Log("Window Created | Opengl Context Created");
	Log("window size width: {} height: {}" , _size.x , _size.y);
	

	if(Texture::Get().size() > 0){
		Log("Texture Pool Size: {}" , Texture::Get().size());
	}

	printf("\n");
	printf("\n");
}

void clearColor(Vec3 Color)
{
	glClearColor(Color.x ,Color.y,Color.z, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
}

void End()
{
	RGFW_window_swapBuffers_OpenGL(getWindow());

}

bool windowShouldClose(){
	return RGFW_window_shouldClose(getWindow());
}

Vec2 getWindowSize(){
	return _size;
}

void closeWindow(){
	RGFW_window_close(getWindow());
}

RGFW_window* getWindow(){
	return static_cast<RGFW_window*>(_window);
}

RGFW_event& getEvent(){
	return _Event;
}

float getDeltaTime(){
	static auto lastTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	std::chrono::duration<float> delta = currentTime - lastTime;
	lastTime = currentTime;

	float dt = delta.count();
	const float max_dt = 0.05f;   
    if (dt > max_dt)
        dt = max_dt;

    return dt;
}


void BeginDrawing()
{
	if(RGFW_window_checkEvent(getWindow() ,&_Event)){
		Input::Update();
	}
	
}

