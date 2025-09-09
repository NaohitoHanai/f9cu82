#include "Player.h"
#include <assert.h>
#include "Stage.h"
#include "Camera.h"

Player::Player() : Player(VGet(0,0,0), 0.0f){}

Player::Player(const VECTOR3& pos, float rot)
{
	const std::string folder = "data/model/Character/Player/";
	// �L�������f����ǂ�
	hModel = MV1LoadModel((folder + "PC.mv1").c_str());
	assert(hModel > 0);
	// ���[�g�m�[�h��Y����]����
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

	// ���͂��x�N�g���ɒ���
	VECTOR3 inputVec = VECTOR3(0,0,0);
	if (CheckHitKey(KEY_INPUT_W)) {
		inputVec += VECTOR3(0,0,1);
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
	// �i�݂����x�N�g�������߂�i���ۂɐi�ރx�N�g���j
	//�@�@�@�J�����̉�]�́Acamera->GetTransform().rotation�Ŏ�ɓ���
	if (inputVec.Size() > 0) {
		moveVec = inputVec * MGetRotY(camera->GetTransform().rotation.y);
		VECTOR3 front = VECTOR3(0, 0, 1) * MGetRotY(transform.rotation.y);
		VECTOR3 right = VECTOR3(1, 0, 0) * MGetRotY(transform.rotation.y);
		float moveCos = VDot(moveVec, front);
		if (moveCos >= cosf(30.0f * DegToRad)) { // ���ʕt��
			transform.position += moveVec * 5.0f;
			transform.rotation.y = atan2f(moveVec.x, moveVec.z);
		} else if (�E�x�N�g���Ƃ̓��ς�>=0) {
			transform.rotation.y += 30.0f * DegToRad;
		} else {
			// �����
		}
	}

	// ��]�����킹��i�P�t���[����60�x���j�F�p�x������Ȃ���ΐi�܂Ȃ�
	// �p�x�������Ă���΁A���̌����ɐi��

	camera->SetPlayerPosition(transform.position);
}

void Player::Draw()
{	
	Object3D::Draw(); // �L�����̕\��
	DrawLine3D(transform.position + moveVec*100, transform.position,
		GetColor(255,0,0));
}
