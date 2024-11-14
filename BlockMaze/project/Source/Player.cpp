#include "Player.h"
#include "Stage.h"
#include "GoalText.h"

const float Gravity = 0.3f;
const float JumpHeight = 40 * 2;
const float V0 = -sqrtf(2.0f * Gravity * JumpHeight);

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;
	goaled = false;
	
}

Player::~Player()
{
}

void Player::Update()
{
	Stage* s = FindGameObject<Stage>();
	if (goaled == false) {
		if (CheckHitKey(KEY_INPUT_A)) {
			position.x -= 2;
			int push = s->IsWallLeft(position + VECTOR2(0, 0));
			position.x += push;
			push = s->IsWallLeft(position + VECTOR2(0, 39));
			position.x += push;
		}
		if (CheckHitKey(KEY_INPUT_D)) {
			position.x += 2;
			// �E�ɕǂ����邩���ׂ�
			int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
			push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
		}
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (prevJumpKey == false) {
				if (onGround) {
					// �W�����v�J�n
					velocity = V0; // ���������߂�
				}
			}
			prevJumpKey = true;
		}
		else {
			prevJumpKey = false;
		}
	}
	position.y += velocity; // ���W�ɂ͑��x�𑫂�
	velocity += Gravity; // ���x�ɂ͏d�͂𑫂�
	onGround = false;
	if (velocity >= 0) {
		int push = s->IsWallDown(position + VECTOR2(0, 40));
		// �W�����v�̑����`�F�b�N�́A�P�h�b�g�������āA
		// �����Ԃ��ʂ́A-1����
		if (push > 0) { // �n�ʂɐG�ꂽ�̂�
			velocity = 0.0f; // �n�ʂɐG�����瑬�x��0�ɂ���
			position.y -= push - 1; // �n�ʂ̏�ɉ����Ԃ�
			onGround = true;
		}

		push = s->IsWallDown(position + VECTOR2(39, 40));
		if (push > 0) {
			velocity = 0.0f;
			position.y -= push - 1;
			onGround = true;
		}
	}
	else {
		int push = s->IsWallUp(position + VECTOR2(0, 0));
		if (push > 0) {
			velocity = 0.0f;
			position.y += push;
		}
		push = s->IsWallUp(position + VECTOR2(39, 0));
		if (push > 0) {
			velocity = 0.0f;
			position.y += push;
		}
	}
	if (position.x - s->scroll > 400) {
		s->scroll = position.x - 400;
	}
	if (position.x - s->scroll < 0) {
		s->scroll = position.x;
	}

	if (s->IsGoal(position+VECTOR2(20,20))) {
		goaled = true;
		Instantiate<GoalText>();
	}
}

void Player::Draw()
{
	Stage* s = FindGameObject<Stage>();
	DrawRectGraph(position.x - s->scroll, position.y, 0, 0, 40, 40, hImage, TRUE);
}
