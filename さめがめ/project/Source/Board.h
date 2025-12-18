#pragma once
#include "../Library/GameObject.h"
#include <vector>

class Board : public GameObject
{
public:
	Board();
	~Board();
	void Update() override;
	void Draw() override;
private:
	int hImage;

	enum Color {
		Red = 0,
		Green,
		Blue,
		Yellow,
		Purple,
		Wall,
		No = -1,
	};
	struct CellInfo {
		int color;
		bool erase;
		float dy; // Y座標をずらす
	};
	std::vector<std::vector<CellInfo>> cells;

	POINT select; // マウスで選択している場所

	void Clear();
	int Check(int x, int y);
	void Erase();
	void Fall();
	float fallSpeed;
};