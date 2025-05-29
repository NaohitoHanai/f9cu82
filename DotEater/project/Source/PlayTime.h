#pragma once
#include "Object3D.h"

class PlayTime : public Object3D
{
public:
	PlayTime();
	~PlayTime();
	void Update() override;
	void Draw() override;

	// TimeUP‚µ‚½‚çtrue
	bool TimeUp();
private:
	float timer;
};