#pragma once
#include "Object3D.h"
#include "Animator.h"

class Goblin : public Object3D {
public:
	Goblin();
	Goblin(const VECTOR& pos, float rot);
	~Goblin();
	void Update() override;
	void CheckAttack(VECTOR3 p1, VECTOR3 p2);
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
		ST_WAIT = 0, // ‘Ò‹@
		ST_CHASE,
		ST_ATTACK,
		ST_BACK,
		ST_DAMAGE,
	};
	State state;
	void UpdateWait();
	void UpdateChase();
	void UpdateAttack();
	void UpdateBack();
	void UpdateDamage();

	struct CircleRange {
		VECTOR center;
		float range;
	};
	CircleRange territory;
};