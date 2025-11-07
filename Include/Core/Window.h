#pragma once
#include "utility/Types.h"
#include "utility/Maths.h"
#include "utility/Colors.h"


#define BeginDraw \
	BeginDrawing()

#define EndDraw \
	End()

struct RGFW_window;
union RGFW_event;

extern RGFW_window* _window; 
extern RGFW_event _Event;

inline static Vec2 _size = Vec2::Zero();
void createWindow(int width , int height , string title);
bool windowShouldClose();
void End();
void clearColor(Vec3 Color);
void closeWindow();
void BeginDrawing();

void setTileName(string newName);
void setWindowOpacity(int value);
void setCursor(bool value);
void setDecorator(bool value);

void getInfo();
Vec2 getWindowSize();
RGFW_window* getWindow();
RGFW_event& getEvent();
float getDeltaTime();
