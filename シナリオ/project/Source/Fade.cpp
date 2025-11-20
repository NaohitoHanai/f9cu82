#include "Fade.h"
#include "Screen.h"

Fade::Fade()
{
	SetDrawOrder(-100);
	startAlpha = 0;
	endAlpha = 0;
	alpha = 0;
	maxTime = 0;
	nowTime = 0;
}

Fade::~Fade()
{
}

float Lerp(float start, float end, float rate)
{
	return (end-start)*rate + start;
}

void Fade::Update()
{
	nowTime += Time::DeltaTime();
	if (nowTime > maxTime)
		nowTime = maxTime;
	if (maxTime == 0.0f) {
		alpha = endAlpha;
	} else {
		alpha = Lerp(startAlpha, endAlpha, nowTime/maxTime);
	}
}

void Fade::Draw()
{
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Screen::WIDTH, Screen::HEIGHT, color, 1);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void Fade::FadeIn(std::string col, float time)
{
	if (col=="BLACK")
		color = GetColor(0, 0, 0);
	maxTime = time;
	nowTime = 0;
	startAlpha = 255;
	endAlpha = 0;
}

void Fade::FadeOut(std::string col, float time)
{
	if (col == "BLACK")
		color = GetColor(0, 0, 0);
	maxTime = time;
	nowTime = 0;
	startAlpha = 0;
	endAlpha = 255;
}

bool Fade::Finished()
{
	return (nowTime >= maxTime);
}
