#include "Coin.h"

Coin::Coin()
{
	hImage = LoadGraph("data/image/parts.png");
}

Coin::~Coin()
{
}

void Coin::Update()
{
}

void Coin::Draw()
{
	DrawRectGraph(position.x, position.y, 120, 0, 40, 40, hImage, TRUE);
}
