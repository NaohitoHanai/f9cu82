#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"

Player::Player() : Player(VGet(0,0,0), 0.0f){}

Player::Player(const VECTOR3& pos, float rot)
{
	const std::string folder = "data/model/Character/Player/";
	// キャラモデルを読む
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ルートノードをY軸回転する
	int root = MV1SearchFrame(hModel, "root");
	MV1SetFrameUserLocalMatrix(hModel, root, MGetRotY(DX_PI_F));

	animator = new Animator(hModel);
	assert(animator != nullptr);
	animator->AddFile(A_NEUTRAL,    folder + "Anim_Neutral.mv1",    true);
	animator->AddFile(A_RUN,        folder + "Anim_Run.mv1",        true);
	animator->AddFile(A_ATTACK1,    folder + "Anim_Attack1.mv1",    false);
	animator->AddFile(A_ATTACK2,    folder + "Anim_Attack2.mv1",    false);
	animator->AddFile(A_ATTACK3,    folder + "Anim_Attack3.mv1",    false);
	animator->AddFile(A_DAMAGE,     folder + "Anim_Damage.mv1",     false);
	animator->AddFile(A_BLOW_IN,    folder + "Anim_Blow_In.mv1",    false);
	animator->AddFile(A_BLOW_LOOP,  folder + "Anim_Blow_Loop.mv1",  true);
	animator->AddFile(A_BLOW_OUT,   folder + "Anim_Blow_Out.mv1",   false);
	animator->AddFile(A_DOWN,       folder + "Anim_Down_Loop.mv1",  true);
	animator->AddFile(A_GUARD_IN,   folder + "Anim_Guard_In.mv1",   false);
	animator->AddFile(A_GUARD_LOOP, folder + "Anim_Guard_Loop.mv1", true);
	animator->AddFile(A_GUARD_OUT,  folder + "Anim_Guard_Out.mv1",  false);
	animator->AddFile(A_JUMP_IN,    folder + "Anim_Jump_In.mv1",    false);
	animator->AddFile(A_JUMP_LOOP,  folder + "Anim_Jump_Loop.mv1",  true);
	animator->AddFile(A_JUMP_OUT,   folder + "Anim_Jump_Out.mv1",   false);
	animator->Play(A_NEUTRAL);

	transform.position = pos;
	transform.rotation.y = rot;

	camera = FindGameObject<Camera>();

	hSabel = MV1LoadModel("data/model/Character/Weapon/Sabel/Sabel.mv1");
	assert(hSabel > 0);
	
	state = ST_NORMAL;
}

Player::~Player()
{
	if (hModel > 0)
	{
		MV1DeleteModel(hModel);
		hModel = -1;
	}
	if (animator != nullptr) {
		delete animator;
		animator = nullptr;
	}
}
VECTOR3 moveVec;

void Player::Update()
{
	animator->Update();
	switch (state) {
	case ST_NORMAL:
		UpdateNormal();
		break;
	case ST_ATTACK1:
		UpdateAttack1();
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
	camera->SetPlayerPosition(transform.position);
}

void Player::Draw()
{	
	Object3D::Draw(); // キャラの表示
	DrawLine3D(transform.position + moveVec*100, transform.position,
		GetColor(255,0,0));

	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	VECTOR s1 = VGet(0,0,0) * m;
	VECTOR s2 = VGet(0,-100,0) * m;
	DrawLine3D(s1, s2, GetColor(255,0,0));
}

void Player::UpdateNormal()
{
	// 入力をベクトルに直す
	VECTOR3 inputVec = VECTOR3(0, 0, 0);
	if (CheckHitKey(KEY_INPUT_W)) {
		inputVec += VECTOR3(0, 0, 1);
	}
	if (CheckHitKey(KEY_INPUT_S)) {
		inputVec += VECTOR3(0, 0, -1);
	}
	if (CheckHitKey(KEY_INPUT_D)) {
		inputVec += VECTOR3(1, 0, 0);
	}
	if (CheckHitKey(KEY_INPUT_A)) {
		inputVec += VECTOR3(-1, 0, 0);
	}
	inputVec = inputVec.Normalize();
	// 進みたいベクトルを求める（実際に進むベクトル）
	//　　　カメラの回転は、camera->GetTransform().rotationで手に入る
	if (inputVec.Size() > 0) {
		animator->Play(A_RUN);
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);
		float moveCos = VDot(moveVec, front);
		if (moveCos >= cosf(30.0f * DegToRad)) { // 正面付近
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		} else if (VDot(moveVec, right) >= 0) {
			transform.rotation.y += 30.0f * DegToRad;
		} else {
			transform.rotation.y -= 30.0f * DegToRad;
		}
	} else {
		animator->Play(A_NEUTRAL);
	}
	if (CheckHitKey(KEY_INPUT_M)) // 攻撃
	{
		animator->Play(A_ATTACK1);
		state = ST_ATTACK1; //状態を変える
	}
}

void Player::UpdateAttack1()
{
	if (animator->IsFinish()) { // 攻撃アニメーションが終わった
		state = ST_NORMAL; //状態を変える
	}
}
