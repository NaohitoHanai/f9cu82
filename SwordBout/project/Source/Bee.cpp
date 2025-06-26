#include "Bee.h"
#include <assert.h>
#include "Stage.h"

Bee::Bee() : Bee(VGet(0, 0, 0), 0.0f){}

Bee::Bee(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Bee/";
	hModel = MV1LoadModel((folder + "Bee.mv1").c_str());
	assert(hModel > 0);

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);

	animator->AddFile(A_NEUTRAL, folder + "Anim_Neutral.mv1", true);
	animator->AddFile(A_WALK,    folder + "Anim_Walk.mv1",    true);
	animator->AddFile(A_RUN,     folder + "Anim_Run.mv1",     true);
	animator->AddFile(A_ATTACK1, folder + "Anim_Attack1.mv1", false);
	animator->AddFile(A_ATTACK2, folder + "Anim_Attack2.mv1", false);
	animator->AddFile(A_DAMAGE,  folder + "Anim_Damage.mv1",  false);
	animator->AddFile(A_DOWN,    folder + "Anim_Down.mv1",    true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;
}

Bee::~Bee()
{
	if (animator!=nullptr) {
		delete animator;
		animator = nullptr;
	}

	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Bee::Update()
{
	animator->Update();
}