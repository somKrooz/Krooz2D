#include "EngineCore/Input.h"
#include "External/WindowBind.h"
#include "Pipeline/Camera.h"
#include "algorithm"


void Input::InitInput(float val)
{
	scrollFactor = val;
}

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

	if(event.type == RGFW_mouseScroll){
		scrollFactor += (float)event.scroll.y * 0.1f;
		event.scroll.y = 0.0f;
	}

} 
float& Input::GetScrollData()
{
	scrollFactor = std::clamp(scrollFactor , 0.1f , 10.0f);
	return scrollFactor;
}
