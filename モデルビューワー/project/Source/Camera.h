#pragma once
#include "../Library/GameObject.h"

class Camera : public GameObject
{
public:
	Camera();
	~Camera();
	void Update() override;
	void Draw() override;
private:
	VECTOR rotation;
	float distance; // ƒJƒƒ‰‚Ì‹——£
};

