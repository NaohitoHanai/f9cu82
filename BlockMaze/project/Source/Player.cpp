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
			// 右に壁があるか調べる
			int push = s->IsWallRight(position + VECTOR2(39, 0));
			position.x -= push;
			push = s->IsWallRight(position + VECTOR2(39, 39));
			position.x -= push;
		}
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			if (prevJumpKey == false) {
				if (onGround) {
					// ジャンプ開始
					velocity = V0; // 初速を決める
				}
			}
			prevJumpKey = true;
		}
		else {
			prevJumpKey = false;
		}
	}
	position.y += velocity; // 座標には速度を足す
	velocity += Gravity; // 速度には重力を足す
	onGround = false;
	if (velocity >= 0) {
		int push = s->IsWallDown(position + VECTOR2(0, 40));
		// ジャンプの足元チェックは、１ドット下を見て、
		// 押し返す量は、-1する
		if (push > 0) { // 地面に触れたので
			velocity = 0.0f; // 地面に触ったら速度を0にする
			position.y -= push - 1; // 地面の上に押し返す
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
