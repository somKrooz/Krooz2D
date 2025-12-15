#include "EngineCore/Input.h"
#include "External/WindowBind.h"
#include "algorithm"


bool Input::IsKeyPressed(int key){
	return CurrenKey[key];
}

bool Input::IsKeyReleased(int key) {
	return !CurrenKey[key] && LastKey[key]; 
}

bool Input::IsJustPressed(int key) {
	return CurrenKey[key] && !LastKey[key]; 
}


void Input::Update(RGFW_event& event){
	
	memcpy(LastKey, CurrenKey, sizeof(CurrenKey));
	if(event.type == RGFW_keyPressed){
		CurrenKey[event.key.value] = true;
	}
	else if(event.type == RGFW_keyReleased){
		CurrenKey[event.key.value] = false;
	}
} 

