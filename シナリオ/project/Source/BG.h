#pragma once
//BG.h
#include "../Library/GameObject.h"

class BG : public GameObject
{
public:
	BG();
	~BG();
	void Set(std::string filename);
	void Update() override;
	void Draw() override;
private:
	int hImage;
	VECTOR2 position;
};
