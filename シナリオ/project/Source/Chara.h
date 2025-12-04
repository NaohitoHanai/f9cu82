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
	void Set(std::string filename);
	void Move(int x, int y, float time);
	bool Finished();
private:
	int hImage;
	VECTOR2 position;
	VECTOR2 startPos;
	VECTOR2 endPos;
	float maxTime;
	float nowTime;
};