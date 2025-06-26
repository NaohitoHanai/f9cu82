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
	int hImage; // �摜
	int number;
	VECTOR3 position; // ���W
	VECTOR3 velocity; // �ړ��ʁi�x�N�g���j
	VECTOR3 addVelocity; // ���velocity�ɑ���
	int catchX, catchY;
	bool catched;
};

















