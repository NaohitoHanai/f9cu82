#pragma once
#include "Enemy.h"
#include "Animator.h"

class RedGoblin : public Enemy {
public:
	RedGoblin();
	RedGoblin(const VECTOR& pos, float rot);
	~RedGoblin();
	void Update() override;
	void CheckAttack(VECTOR3 p1, VECTOR3 p2) override;
private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_WALK,
		A_RUN,
		A_ATTACK1,
		A_DAMAGE,
		A_BLOW_IN,
		A_BLOW_LOOP,
		A_BLOW_OUT,
		A_DOWN,
	};
	Animator* animator;
	enum State {
		ST_WAIT = 0,
		ST_DAMAGE,
	};
	State state;
	void UpdateWait();
	void UpdateDamage();
};