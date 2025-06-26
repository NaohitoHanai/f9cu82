#pragma once
#include "Object3D.h"
#include "Animator.h"

class Bee : public Object3D {
public:
	Bee();
	Bee(const VECTOR& pos, float rot);
	~Bee();
	void Update() override;
private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_WALK,
		A_RUN,
		A_ATTACK1,
		A_ATTACK2,
		A_DAMAGE,
		A_DOWN,
	};
	Animator* animator;
};