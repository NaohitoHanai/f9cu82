#pragma once
#include "../Library/GameObject.h"

class Ball : public GameObject
{
public:
	Ball(int num, VECTOR3 pos);
	~Ball();
	void Update() override;
	void Draw() override;
private:
	int hImage; // 画像
	int number;
	VECTOR3 position; // 座標
	VECTOR3 velocity; // 移動量（ベクトル）

	int catchX, catchY;
	bool catched;
};

















