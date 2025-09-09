#pragma once
#include "Object3D.h"
#include "Animator.h"
#include "StateBase.h"
class Camera;

class Player : public Object3D
{
public:
	Player();
	Player(const VECTOR3& pos, float rot);
	~Player();
	void Update() override;
	void Draw() override;
private:
	enum AnimID {
		A_NEUTRAL = 0,
		A_RUN,
		A_ATTACK1,
		A_ATTACK2,
		A_ATTACK3,
		A_DAMAGE,
		A_BLOW_IN,
		A_BLOW_LOOP,
		A_BLOW_OUT,
		A_DOWN,
		A_GUARD_IN,
		A_GUARD_LOOP,
		A_GUARD_OUT,
		A_JUMP_IN,
		A_JUMP_LOOP,
		A_JUMP_OUT,
		A_MAX
	};
	Animator* animator;
	Camera* camera;
};