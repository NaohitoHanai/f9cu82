#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1");
	rotation = VGet(0, 0, 0);
}

Model::~Model()
{
}

void Model::Update()
{
	rotation.y += 180.0f * Time::DeltaTime() * DegToRad;
}

void Model::Draw()
{
	MV1SetRotationXYZ(hModel, rotation);
	MV1SetPosition(hModel, VGet(0, 0, 0));
	MV1DrawModel(hModel);
}
