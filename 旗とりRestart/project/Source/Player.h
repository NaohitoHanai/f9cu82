#pragma once
#include "../Library/gameObject.h"
#include "Vector2.h"

class Player : public GameObject {
public:
	Player();
	~Player();
	void Update() override;
	void Draw() override;

	void CryAnimation(); // こういう関数を作る

	int hImage; // 画像

	VECTOR2 position;
	VECTOR2 speed;

	int patternX; // アニメーションの絵
	int patternY;
	int frameCounter;

	bool crying; // 泣いてるときtrue

	bool prevKey; // 前のキーを保存する
};