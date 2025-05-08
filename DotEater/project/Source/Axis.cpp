#include "Axis.h"

Axis::Axis()
{
}

Axis::~Axis()
{
}

void Axis::Update()
{
}

void Axis::Draw()
{
//	SetCameraPositionAndTarget_UpVecY(VGet(100, 200, -300), VGet(0, 0, 0));
//	SetCameraPositionAndTarget_UpVecY(VGet(0, 300, -10), VGet(0, 0, 0));

	DrawLine3D(VGet(-100, 0, 0), VGet(100, 0, 0), GetColor(255, 0, 0));
	DrawCone3D(VGet(100,0,0), VGet(80,0,0), 20, 20, GetColor(255,0,0), GetColor(255,0,0), 1); 
	DrawLine3D(VGet(0, -100, 0), VGet(0, 100, 0), GetColor(0, 255, 0));
	DrawLine3D(VGet(0, 0, -100), VGet(0, 0, 100), GetColor(0, 0, 255));
}
