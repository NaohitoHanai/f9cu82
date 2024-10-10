#include "Stone.h"
#include "config.h"

Stone::Stone()
{
	hImage = LoadGraph("data/image/stone.png");
	position.x = 10;
	position.y = 100;
}

Stone::~Stone()
{
	DeleteGraph(hImage);
}

void Stone::Update()
{
	position.x += 5.0f;
	if (position.x > SCREEN_WIDTH) {
		DestroyMe();
	}
}

void Stone::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
	DrawCircle(position.x + 8, position.y + 8, 8, GetColor(255, 0, 0), 0);
}
