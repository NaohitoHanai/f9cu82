#pragma once
#include "../Library/GameObject.h"

class Model : public GameObject
{
public:
	Model();
	~Model();
	void Update() override;
	void Draw() override;
private:
	int hModel;
	VECTOR rotation;
};