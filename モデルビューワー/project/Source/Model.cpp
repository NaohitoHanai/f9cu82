#include "Model.h"

Model::Model()
{
	hModel = MV1LoadModel("data/Fighter.mv1");
	rotation = VGet(0, 0, 0);
	position = VGet(0, 0, 0);
}

Model::~Model()
{
}

void Model::Update()
{
	if (CheckHitKey(KEY_INPUT_D)) {
		rotation.y += 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		rotation.y -= 3.0f * DegToRad;
	}
	if (CheckHitKey(KEY_INPUT_W)) {
		// ëOÇ…êiÇﬁ
		VECTOR velocity = VGet(0,0,1) * MGetRotX(rotation.x) * MGetRotY(rotation.y);
		position += velocity;
	}
}
