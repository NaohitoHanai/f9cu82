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
	void CheckAttack(VECTOR3 p1, VECTOR3 p2);
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

	int hSabel;

	// èÛë‘ëJà⁄
	enum State {
		ST_NORMAL = 0,
		ST_ATTACK1,
		ST_ATTACK2,
		ST_ATTACK3,
		ST_DAMAGE,
	};
	State state; // èÛë‘ÇéùÇ¬ïœêî
	void UpdateNormal();
	void UpdateAttack1();
	void UpdateAttack2();
	void UpdateAttack3();
	void UpdateDamage();

	bool attackNext;
	VECTOR sabelBtm;
	VECTOR sabelTop;

	struct AnimParam {
		float time;
		std::string com;
		std::string file;
	};
	std::list<AnimParam> animParam;
	void LoadParam(std::string filename);
	bool attackEnable;
};	