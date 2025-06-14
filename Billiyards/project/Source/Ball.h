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
	int hImage; // �摜
	int number;
	VECTOR3 position; // ���W
	VECTOR3 velocity; // �ړ��ʁi�x�N�g���j

	int catchX, catchY;
	bool catched;
};

















