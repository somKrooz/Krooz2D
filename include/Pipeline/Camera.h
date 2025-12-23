#pragma once
#include "Utility/Types.h"
#include "Utility/Maths.h"
#include "Components/TransformComponent.h"
#include "STB/FastNoiseLite.h"
struct Camera
{
	inline static Mat4 viewMatrix = Mat4::identity();
	inline static Mat4 projectionMatrix = Mat4::identity();
	inline static bool isCamera = false;
	inline static bool isCameraShaking = false;
	inline static fnl_state noise;

	Vec2 Position = Vec2::Zero();
	inline static float Zoom = 1.0f;
	TransformComponent* local = nullptr;

	Camera();
	void setTarget(TransformComponent& trs);
	void setZoomLerp(float value, float dt);
	void Update(float delta);
	static void setZoom(float value);
	static bool isCameraExist();
	static void ShakeCam();
	static float GetZoom();
	static Mat4& GetView();
	static Mat4& GetProjection();
};
