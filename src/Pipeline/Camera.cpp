#define FNL_IMPL
#include "Pipeline/Camera.h"

Camera::Camera()
{
    isCamera = true;
	if(Zoom == 0.0f)
	{
		Zoom = 1.0f;
	}

    noise = fnlCreateState();
    noise.seed = 1337;
    noise.noise_type = FNL_NOISE_OPENSIMPLEX2;
    noise.frequency = 10.0f;
}

void Camera::ShakeCam()
{
	isCameraShaking = true;
}

void Camera::Update(float delta)
{
    static float t = 0.0f;
    static float amount = 0.0f;
    if(isCameraShaking){
		amount += delta;
		t += delta * 40.0f;
	
		float shakeX = fnlGetNoise2D(&noise, t, 0.0f);
		float shakeY = fnlGetNoise2D(&noise, 0.0f, t);

		Position.x += shakeX;
    	Position.y += shakeY;
		if(amount >= 0.2f){
			amount = 0.0f;
			isCameraShaking = false;
		}
	}

    float lerpFactor = 6.0f * delta;
    Position = Vec2::mix(Position, local->GetPosition(), lerpFactor);


    Vec2 ActorCenter = Position + local->GetScaleVec() * 0.5f;
    Vec2 ScreenCenter = Vec2(1280 / 2, 720 / 2);

    viewMatrix = Mat4::translate(ScreenCenter - ActorCenter);

    float invZoom = 1.0f / Zoom;
    float hZx = (1280 * invZoom) * 0.5f;
    float hZy = (720 * invZoom) * 0.5f;

    projectionMatrix = Mat4::ortho(
        ScreenCenter.x - hZx, ScreenCenter.x + hZx,
        ScreenCenter.y + hZy, ScreenCenter.y - hZy,
        -1, 1
    );
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

void Camera::setZoom(float value)
{
	Zoom = value;
}

void Camera::setZoomLerp(float value , float dt) {

	float t = 10.0f * dt;
	float currentZoom = Zoom * (1.0f - t) + value * t;
	Zoom = currentZoom;
}

float Camera::GetZoom(){
	return Zoom;
}
