#pragma once
#include "utility/Maths.h"
#include "Core/Window.h"
#include "Components/TransformComponent.h"


struct Camera
{
	private:
	static inline Mat4 ProjectionMatrix = Mat4::ortho(0,getWindowSize().x ,getWindowSize().y,0,-1,1);
	static inline Mat4 ViewMatrix = Mat4::identity();

	void ReCalculateMatrix(){
		Vec2 PlayerCenter = Position + Vec2(target->GetScale()/2,target->GetScale()/2);
		Vec2 ScreenCenter = Vec2( getWindowSize().x/2 , getWindowSize().y/2);
		
		float HalfScreenW = (getWindowSize().x/2) / zoom;
		float HalfScreenH = (getWindowSize().y/2) / zoom;

		ViewMatrix = Mat4::translate(Vec2(ScreenCenter.x - PlayerCenter.x , ScreenCenter.y - PlayerCenter.y));
		ProjectionMatrix = Mat4::ortho(ScreenCenter.x - HalfScreenW , ScreenCenter.x + HalfScreenW,ScreenCenter.y + HalfScreenH, ScreenCenter.y - HalfScreenH,-1,1);
	}

	TransformComponent* target = nullptr;
	Vec2 Position = Vec2::Zero();

	public:
	float zoom = 0.1f;

	Camera()
	{
		ProjectionMatrix = Mat4::ortho(0,getWindowSize().x ,getWindowSize().y,0,-1,1);
		ViewMatrix = Mat4::identity();
	}
	
	void SetTarget(TransformComponent* newTarget) {
		target = newTarget;
		ReCalculateMatrix();
	}
	
	void Follow(float dt){
		float lerpFactor = 6.0f * dt;
		Position = Vec2::mix(Position , target->GetPosition() ,lerpFactor);
		ReCalculateMatrix();
	}

	void setZoom(float val, float dt)
	{
		float t = 10.0f * dt;
		float currentZoom = zoom * (1.0f - t) + val * t;
		zoom = currentZoom;		
	}

	static Mat4& GetMat(){return ViewMatrix;} 
	static Mat4& GetProjection(){return ProjectionMatrix;} 
};

