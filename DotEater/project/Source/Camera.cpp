#include "Camera.h"
#include "../ImGui/imgui.h"

Camera::Camera()
{
//	rotation = VGet(80*DegToRad,0,0);
//	distance = 500.0f;
	rotation = VGet(30 * DegToRad, 0, 0);
	distance = 400.0f;
}

Camera::~Camera()
{
}

void Camera::Update()
{
}

void Camera::Draw()
{
	VECTOR pos = VGet(0,0,-distance) * MGetRotX(rotation.x) * MGetRotY(rotation.y);
	SetCameraPositionAndTarget_UpVecY(pos, VGet(0, 0, 0));
}
