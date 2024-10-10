#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Bird : public GameObject {
public:
	Bird();
	~Bird();
	void Update() override;
	void Draw() override;

	int hImage; // 画像
	VECTOR2 position;
	VECTOR2 speed;
	int patternX; // アニメーションの絵
	int patternY;
	int frameCounter;

	int timer; // 時間を測るため
	bool attacking; // 突入してます

	bool dead; // 死んだらtrue
	int deadCounter; // 死んでる時間
};