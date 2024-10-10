#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Stone : public GameObject {
public:
	Stone();
	~Stone();
	void Update() override;
	void Draw() override;

	int hImage; // ‰æ‘œ
	VECTOR2 position;
};