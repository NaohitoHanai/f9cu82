#pragma once
#include "../Library/GameObject.h"

class Ball : public GameObject
{
public:
	Ball(int num, VECTOR3 pos);
	~Ball();
	void Update() override;
	void Draw() override;
	VECTOR3 GetPosition() { return position; }
	void AddForce(VECTOR3 force);
	void HitOtherBall(Ball* other);
private:
	int hImage; // 画像
	int number;
	VECTOR3 position; // 座標
	VECTOR3 velocity; // 移動量（ベクトル）
	VECTOR3 addVelocity; // 後でvelocityに足す
	int catchX, catchY;
	bool catched;
};

















