#pragma once
#include "Object3D.h"

class PlayTime : public Object3D
{
public:
	PlayTime();
	~PlayTime();
	void Update() override;
	void Draw() override;

	// TimeUP������true
	bool TimeUp();
private:
	float timer;
};