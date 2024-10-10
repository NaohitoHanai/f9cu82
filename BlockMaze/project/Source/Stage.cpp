#include "Stage.h"

Stage::Stage()
{
	hImage = LoadGraph("data/image/parts.png");
}

Stage::~Stage()
{
}

void Stage::Draw()
{
	DrawRectGraph(100, 100, 0, 40, 40, 40, hImage, TRUE);
}
