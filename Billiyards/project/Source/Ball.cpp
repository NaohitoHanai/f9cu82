#include "Ball.h"
#include "Screen.h"

Ball::Ball(int num, VECTOR3 pos)
{
	hImage = LoadGraph("data/textures/billiyard.png");
	number = num;
	position = pos;
	velocity = VECTOR3(1, 0.5f, 0)*10; // 右に移動
	catched = false;
}

Ball::~Ball()
{
}

void Ball::Update()
{
	if (catched) {
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) == 0) {
			// 左ボタンを離したので
			int x, y;
			GetMousePoint(&x, &y);
			velocity = VECTOR3(catchX - x, catchY - y, 0) / 20.0f;
			catched = false;
		}
	} else {
		if (GetMouseInput() & MOUSE_INPUT_LEFT) {
			// 左クリックした時の座標を取っておく
			catched = true;
			GetMousePoint(&catchX, &catchY);
		}
	}

	position += velocity;
	if (position.y >= Screen::HEIGHT - 28) {
		velocity.y *= -1.0f;
	}
	if (position.y < 0 + 28) {
		velocity.y *= -1.0f;
	}
	if (position.x >= Screen::WIDTH - 28) {
		velocity.x *= -1.0f;
	}
	if (position.x < 0 + 28) {
		velocity.x *= -1.0f;
	}
	// 毎フレーム一定量を減らす
	float len = velocity.Size();	// velocityベクトルの長さを求める
	len -= 0.01f;	// 長さを一定値減らす

	if (len <= 0.0f)	// 長さが0以下になれば、velocityは(0,0,0)
	{
		velocity = VECTOR3(0, 0, 0);
	}
	else
	{
		velocity = velocity.Normalize() * len;	// velocityを、その長さに書き換える
	}
}

void Ball::Draw()
{
	int x = (number - 1) % 4;
	int y = (number - 1) / 4;
	DrawRectGraph(position.x-32, position.y-32, x*64, y*64, 64, 64, hImage, TRUE);
}
