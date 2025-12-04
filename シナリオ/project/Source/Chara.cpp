#include "Chara.h"
#include "Screen.h"

Chara::Chara()
{
}

Chara::~Chara()
{
}

VECTOR2 Lerp(VECTOR2 start, VECTOR2 end, float rate)
{
	return (end - start) * rate + start;
}


void Chara::Update()
{
	nowTime += Time::DeltaTime();
	if (nowTime > maxTime)
		nowTime = maxTime;
	if (maxTime == 0.0f) {
		position = endPos;
	} else {
		position = Lerp(startPos, endPos, nowTime / maxTime);
	}

}

void Chara::Draw()
{
	DrawGraph(position.x, position.y, hImage, TRUE);
}

void Chara::Set(std::string filename)
{
	std::string folder = "data/textures/";
	hImage = LoadGraph((folder + filename).c_str());
}

void Chara::Move(int x, int y, float time)
{
	int ix, iy;
	GetGraphSize(hImage, &ix, &iy);
	startPos = position;
	endPos.x = x + Screen::WIDTH/2 - ix/2;
	endPos.y = y;
	maxTime = time;
	nowTime = 0;
	// timeの秒数で、キャラクターを移動させる
	// position.xに-800が入ってて、
	// x=-300,time=0.5で呼ばれたら
	// position.xが-800から、-300へ0.5秒で移動
}

bool Chara::Finished()
{
	// 移動が終わったらtrueを返す
	return nowTime >= maxTime;
}
