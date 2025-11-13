#pragma once
// Chara.h
#include "../Library/GameObject.h"

class Chara : public GameObject
{
public:
	Chara();
	~Chara();
	void Update() override;
	void Draw() override;
private:
	int hImage;
	VECTOR2 position;
};