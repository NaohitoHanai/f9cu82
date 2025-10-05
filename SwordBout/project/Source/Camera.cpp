#include "Camera.h"
#include "PadInput.h"

namespace {
	static float distance = 500.0f; // ƒLƒƒƒ‰‚©‚ç‚Ì‹——£
	static float lookHeight = 200.0f; // ’‹“_‚Ì‚‚³
};

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	PadInput* pad = FindGameObject<PadInput>();
	float padX = pad->RStickX();
	transform.rotation.y += padX * 3.0f * DegToRad;
	transform.rotation.x += pad->RStickY() * 3.0f * DegToRad;
	if (transform.rotation.x >= 85.0f * DegToRad) {
		transform.rotation.x = 85.0f * DegToRad;
	}
	if (transform.rotation.x <= -45.0f * DegToRad) {
		transform.rotation.x = -45.0f * DegToRad;
	}

	VECTOR3 camPos = lookPosition + VECTOR3(0,150,0)
		+ VECTOR3(0,0,-427) * MGetRotX(transform.rotation.x)
		* MGetRotY(transform.rotation.y);
	VECTOR3 lookPos = lookPosition + VECTOR3(0, 200, 0);
	SetCameraPositionAndTarget_UpVecY(camPos, lookPos);
}

void Camera::Draw()
{
}

void Camera::SetPlayerPosition(const VECTOR& pos)
{
	lookPosition = pos;
}
