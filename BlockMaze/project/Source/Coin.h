#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Coin : public GameObject {
public:
	Coin();
	~Coin();
	void Update() override;
	void Draw() override;

	int hImage;
	VECTOR2 position;
};
