#pragma once
// EnemyManager.h
#include "Object3D.h"
class Enemy; // Enemy‚Á‚ÄƒNƒ‰ƒX‚ª‚ ‚é‚æ

class EnemyManager : public Object3D
{
public:
	EnemyManager();
	~EnemyManager();
	bool RequestAttack(Enemy* e);
	void CancelAttack(Enemy* e);
private:
	std::list<Enemy*> waiting;
};