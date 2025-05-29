#include "ReadyGo.h"
#include "PlayScene.h"

ReadyGo::ReadyGo()
{
	hReady = LoadGraph("data/images/ready.png");
	hGo = LoadGraph("data/images/go.png");
	timer = 1.0f; // •b
}

ReadyGo::~ReadyGo()
{
}

void ReadyGo::Update()
{
	timer -= Time::DeltaTime(); //DeltaTime‚Í1/60•b
	if (timer < -0.5f) {
		DestroyMe();
	}
}

void ReadyGo::Draw()
{
	if (timer > 0.0f) {
		DrawGraph(300, 300, hReady, TRUE);
	} else {
		DrawGraph(300, 0, hGo, TRUE);
	}
}

bool ReadyGo::TimeEnd()
{
	return timer <= 0.0f;
//	if (timer <= 0.0f)
//		return true;
//	return false;
}
