#include "Goblin.h"
#include <assert.h>
#include "Stage.h"
#include "Player.h"
#include "EnemyManager.h"

Goblin::Goblin() : Goblin(VGet(0,0,0), 0.0f) {}

Goblin::Goblin(const VECTOR& pos, float rot)
{
	const std::string folder = "data/model/Character/Goblin/";
	hModel = MV1LoadModel((folder + "Goblin.mv1").c_str());
	assert(hModel > 0);
	MV1SetupCollInfo(hModel);

	hAxe = MV1LoadModel("data/model/Character/Weapon/Axe/Axe.mv1");

	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);

	animator->AddFile(A_NEUTRAL,   folder + "Anim_Neutral.mv1",   true);
	animator->AddFile(A_WALK,      folder + "Anim_Walk.mv1",      true);
	animator->AddFile(A_RUN,       folder + "Anim_Run.mv1",       true);
	animator->AddFile(A_ATTACK1,   folder + "Anim_Attack1.mv1",   false);
	animator->AddFile(A_DAMAGE,    folder + "Anim_Damage.mv1",    false);
	animator->AddFile(A_BLOW_IN,   folder + "Anim_Blow_In.mv1",   false);
	animator->AddFile(A_BLOW_LOOP, folder + "Anim_Blow_Loop.mv1", true);
	animator->AddFile(A_BLOW_OUT,  folder + "Anim_Blow_Out.mv1",  false);
	animator->AddFile(A_DOWN,      folder + "Anim_Down_Loop.mv1",      true);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;
	territory.center = pos;
	territory.range = 2000.0f;

	state = ST_WAIT;
}

Goblin::~Goblin()
{
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}

	if (hModel > 0) {
		MV1DeleteModel(hModel);
		hModel = -1;
	}
}

void Goblin::Update()
{
	animator->Update();
	switch (state)
	{
	case ST_WAIT:
		UpdateWait();
		break;
	case ST_CHASE:
		UpdateChase();
		break;
	case ST_ATTACK:
		UpdateAttack();
		break;
	case ST_BACK:
		UpdateBack();
		break;
	case ST_DAMAGE:
		UpdateDamage();
		break;
	}
	Stage* stage = FindGameObject<Stage>();
	VECTOR hit; // 地面の座標が入る変数
	VECTOR pos1 = transform.position + VGet(0, 100, 0);
	VECTOR pos2 = transform.position + VGet(0, -100, 0);
	if (stage->CollideLine(pos1, pos2, &hit))
	{
		transform.position = hit;
	}
}

void Goblin::Draw()
{
	Object3D::Draw();

	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 20);
	MV1SetMatrix(hAxe, m);
	MV1DrawModel(hAxe);
	// 斧を持たせる　data\model\Character\Weapon\Axe\Axe.mv1
	// 持たせる手は　２０番 hansocketR

	axeBtm = VGet(0, -100, 0) * m;
	axeTop = VGet(0, 80, 0) * m;
	DrawLine3D(axeBtm, axeTop, GetColor(255, 0, 0));
}

void Goblin::CheckAttack(VECTOR3 p1, VECTOR3 p2)
{
	MV1RefreshCollInfo(hModel);
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (ret.HitFlag > 0) {
		animator->Play(A_DAMAGE);
		state = ST_DAMAGE;
	}
}

void Goblin::UpdateWait()
{
	Player* pl = FindGameObject<Player>();
	VECTOR3 plPos = pl->GetTransform().position; // プレイヤーの座標
	VECTOR3 toPlayer = plPos - transform.position;
	// toPlayerの長さが1000以下か？
	if (toPlayer.Size() > 1000)
		return;

	VECTOR3 front = VECTOR3(0,0,1)* MGetRotY(transform.rotation.y);
	// toPlayerの長さ１にしたのと、frontで内積をとる
	float cosT = VDot(toPlayer.Normalize(), front);
	// θが60°以内か？
	if (cosT >= cos(60 * DegToRad)) {
		animator->Play(A_RUN);
		state = ST_CHASE; // 仮
	}
}

void Goblin::UpdateChase()
{
	// プレイヤーに向かって走る
	//　キャラの向いてる方に走る
	Player* pl = FindGameObject<Player>();
	VECTOR3 diff 
		= pl->GetTransform().position - transform.position;
	float d = diff.Size();
	if (d >= 100.0f) {
		d = MoveTo(pl->GetTransform().position, 6);
	}
	// 近づいたらATTACKへ
	if (d < 100.0f) {
		EnemyManager* man = FindGameObject<EnemyManager>();
		if (man->RequestAttack(this)) {
			animator->Play(A_ATTACK1);
			state = ST_ATTACK;
		}
	}
	// テリトリーを出たらWAITにする
	VECTOR3 v = transform.position - territory.center;
	if (v.Size() >= territory.range) {
		animator->Play(A_WALK);
		state = ST_BACK;
	}
}

void Goblin::UpdateAttack()
{
	if (animator->GetCurrentFrame() >= 20.0f) {
		EnemyManager* man = FindGameObject<EnemyManager>();
		man->CancelAttack(this);
	}
	// 攻撃アニメーションが終わったらWAIT
	if (animator->IsFinish()) {
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
	float frame = animator->GetCurrentFrame();
	if (frame < 20.0f) {
		//Playerの方を向く
		Player* pl = FindGameObject<Player>();
		VECTOR3 toPl = pl->GetTransform().position - transform.position;
//		transform.rotation.y = atan2(toPl.x, toPl.z);
		VECTOR3 right = VECTOR3(1,0,0) * transform.GetRotationMatrix();
		if (VDot(right, toPl) > 0) {
			transform.rotation.y += 2.0f * DegToRad;
		} else {
			transform.rotation.y -= 2.0f * DegToRad;
		}
	}
	if (frame >= 24.5 && frame <= 27.5) {
		Player* pl = FindGameObject<Player>();
		pl->CheckAttack(axeBtm, axeTop);
	}
}

void Goblin::UpdateBack()
{
	float d = MoveTo(territory.center, 2);
	if (d < 100.0f) {
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}

}

void Goblin::UpdateDamage()
{
	if (animator->IsFinish())
	{
		animator->Play(A_NEUTRAL);
		state = ST_WAIT;
	}
}

float Goblin::MoveTo(VECTOR3 target, float speed)
{
	VECTOR3 velocity = VECTOR3(0, 0, speed) * MGetRotY(transform.rotation.y);
	transform.position += velocity;
	VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);
	VECTOR3 toTarget = target - transform.position;
	float ip = VDot(right, toTarget);
	if (ip >= 0)
		transform.rotation.y += DegToRad;
	else
		transform.rotation.y -= DegToRad;
	return toTarget.Size();
}
