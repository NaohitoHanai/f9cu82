#include "Object3D.h"

Object3D::Object3D()
{
}

Object3D::~Object3D()
{
}

void Object3D::Update()
{
}

void Object3D::Draw()
{
	MATRIX mrx = MGetRotX(rotation.x); // X軸回転行列
	MATRIX mry = MGetRotY(rotation.y); // Y軸回転行列
	MATRIX mrz = MGetRotZ(rotation.z); // Z軸回転行列
	MATRIX mt = MGetTranslate(position); // 移動行列
	MATRIX m = mrz * mrx * mry * mt;
	MV1SetMatrix(hModel, m);
	MV1DrawModel(hModel);
}
