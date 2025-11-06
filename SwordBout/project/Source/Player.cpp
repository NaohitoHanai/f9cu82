#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"
#include "PadInput.h"
#include "Enemy.h"
#include "CsvReader.h"

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
	case ST_ATTACK2:
		UpdateAttack2();
		break;
	case ST_ATTACK3:
		UpdateAttack3();
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
	camera->SetPlayerPosition(transform.position);
}

void Player::Draw()
{	
	Object3D::Draw(); // キャラの表示

	MATRIX m = MV1GetFrameLocalWorldMatrix(hModel, 29);
	MV1SetMatrix(hSabel, m);
	MV1DrawModel(hSabel);

	sabelBtm = VGet(0,0,0) * m;
	sabelTop = VGet(0,-100,0) * m;
	DrawLine3D(sabelBtm, sabelTop, GetColor(255,0,0));
}

void Player::CheckAttack(VECTOR3 p1, VECTOR3 p2)
{
	MV1RefreshCollInfo(hModel);
	MV1_COLL_RESULT_POLY ret = MV1CollCheck_Line(hModel, -1, p1, p2);
	if (ret.HitFlag > 0) {
		animator->Play(A_DAMAGE);
		state = ST_DAMAGE;
	}
}

void Player::UpdateNormal()
{
	// 入力をベクトルに直す
	VECTOR3 inputVec = VECTOR3(0, 0, 0);
	PadInput* pad = FindGameObject<PadInput>();
	VECTOR2 inp = pad->LStickVec();
	inputVec.x = inp.x;
	inputVec.z = inp.y;
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
	if (pad->OnPush(XINPUT_BUTTON_A)) // 攻撃
	{
		animator->Play(A_ATTACK1);
		attackEnable = false;
		LoadParam("data/model/Character/Player/Anim_Attack1.csv");
		attackNext = false;
		state = ST_ATTACK1; //状態を変える
	}
}

void Player::UpdateAttack1()
{
	float frame = animator->GetCurrentFrame();
	for (AnimParam p : animParam) {
		if (frame >= p.time - 0.5f && frame <= p.time) {
			std::string com = p.com;
			if (com == "Sound") {
				std::string f = "data/sound/SE/";
				PlaySound((f + p.file + ".wav").c_str(),
					DX_PLAYTYPE_BACK);
			}
			if (com == "AttackStart") {
				attackEnable = true;
			}
			if (com == "AttackEnd") {
				attackEnable = false;
			}
		}
	}
	if (animator->GetCurrentFrame() >= 8.5f) {
		if (attackNext) {
			animator->Play(A_ATTACK2);
			attackNext = false;
			state = ST_ATTACK2;
		}
	} else {
		if (attackEnable) {
			std::list<Enemy*> gobs = FindGameObjects<Enemy>();
			for (Enemy* gob : gobs) {
				gob->CheckAttack(sabelBtm, sabelTop);
			}
		}
		PadInput* pad = FindGameObject<PadInput>();
		if (pad->OnPush(XINPUT_BUTTON_A))
		{
			attackNext = true;
		}
	}
	if (animator->IsFinish()) { // 攻撃アニメーションが終わった
		state = ST_NORMAL; //状態を変える
	}
}

void Player::UpdateAttack2()
{
	if (animator->GetCurrentFrame() >= 9.5f) {
		if (attackNext) {
			animator->Play(A_ATTACK3);
			attackNext = false;
			state = ST_ATTACK3;
		}
	} else {
		Enemy* gob = FindGameObject<Enemy>();
		gob->CheckAttack(sabelBtm, sabelTop);

		PadInput* pad = FindGameObject<PadInput>();
		if (pad->OnPush(XINPUT_BUTTON_A))
		{
			attackNext = true;
		}
	}
	if (animator->IsFinish()) { // 攻撃アニメーションが終わった
		state = ST_NORMAL; //状態を変える
	}
}

void Player::UpdateAttack3()
{
	if (animator->IsFinish()) { // 攻撃アニメーションが終わった
		state = ST_NORMAL; //状態を変える
	} else {
		Enemy* gob = FindGameObject<Enemy>();
		gob->CheckAttack(sabelBtm, sabelTop);
	}
}

void Player::UpdateDamage()
{
	if (animator->IsFinish()) { // アニメーションが終わった
		state = ST_NORMAL; //状態を変える
	}
}

void Player::LoadParam(std::string filename)
{
	animParam.clear();
	CsvReader* csv = new CsvReader(filename);
	for (int i = 0; i < csv->GetLines(); i++) {
		AnimParam p;
		p.time = csv->GetFloat(i, 0);
		p.com = csv->GetString(i, 1);
		p.file = csv->GetString(i, 2);
		animParam.push_back(p);
	}
	delete csv;
}