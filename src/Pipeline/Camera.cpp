#include "Pipeline/Camera.h"

Camera::Camera(){
	isCamera = true;
}

void Camera::Update(float delta)
{

	float lerpFactor = 6.0f * delta;
	Position = Vec2::mix(Position , local->GetPosition() ,lerpFactor);

	float CenterX = Position.x + (local->GetScaleVec().x/2);
	float CenterY = Position.y + (local->GetScaleVec().y/2);
	Vec2 ActorCenter = Vec2(CenterX , CenterY); 
	Vec2 ScreenCenter = Vec2(1280/2 , 720/2);
	viewMatrix = Mat4::translate(ScreenCenter - ActorCenter);

	float hZx = (1280 * Zoom) * 0.5;
	float hZy = (720 * Zoom) * 0.5;

	projectionMatrix = Mat4::ortho(ScreenCenter.x - hZx, ScreenCenter.x + hZx, 
	ScreenCenter.y + hZy , ScreenCenter.y - hZy, -1, 1);
}

void Camera::setTarget(TransformComponent& trs){
	local = &trs;
}

bool Camera::isCameraExist()
{
	return isCamera;
}

Mat4& Camera::GetView(){
	return viewMatrix;
}
Mat4& Camera::GetProjection(){
	return projectionMatrix;
}
