#include "Camera.h"

namespace {
	static float distance = 500.0f; // キャラからの距離
	static float lookHeight = 200.0f; // 注視点の高さ
};

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::Update()
{
	SetCameraPositionAndTarget_UpVecY(
			lookPosition + VECTOR3(0, 300.0f, -400.0f),
			lookPosition + VECTOR3(0, 200.0f, 0));
}

void Camera::Draw()
{
}

void Camera::SetPlayerPosition(const VECTOR& pos)
{
	lookPosition = pos;
}
