#include "Core/input.h"
#include "Core/Window.h"
#include "utility/Logs.h"
#include "algorithm"
#include "RGFW.h"


bool Input::IsKeyPressed(int key){
	return CurrenKey[key];
}

bool Input::IsKeyReleased(int key) {
	return !CurrenKey[key] && LastKey[key]; 
}

bool Input::IsJustPressed(int key) {
	return CurrenKey[key] && !LastKey[key]; 
}

void Input::Update(){
	
	auto& event = getEvent();
	memcpy(LastKey, CurrenKey, sizeof(CurrenKey));
	if(event.type == RGFW_keyPressed){
		CurrenKey[event.key.value] = true;
	}
	else if(event.type == RGFW_keyReleased){
		CurrenKey[event.key.value] = false;
	}
} 

float Input::ScrollFactor(){
	auto& event = getEvent();

	if(event.type == RGFW_mouseScroll){
		scrollvalue += (float)event.scroll.y * 0.1f;
		event.scroll.y = 0.0f;
	}
	scrollvalue = std::clamp(scrollvalue , 0.1f , 10.0f);
	return scrollvalue;
} 

