#pragma once
#include "../Library/GameObject.h"

class BallManager : public GameObject
{
public:
	BallManager() {}
	~BallManager() {}
	void Update() override;
};