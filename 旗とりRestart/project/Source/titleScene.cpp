#include "titleScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"

TitleScene::TitleScene()
{
}

TitleScene::~TitleScene()
{
}

void TitleScene::Update()
{
	if (CheckHitKey(KEY_INPUT_P)) {
		SceneManager::ChangeScene("PlayScene");
	}

	SceneBase::Update();
}

int x = 0;

void TitleScene::Draw()
{
	x = x + 1;
	SceneBase::Draw();
	DrawString(x, 0, "TITLE SCENE", GetColor(255,255,255));
	DrawString(100, 400, "Push [P]Key To Play", GetColor(255, 255, 255));
	DrawString(800, 600, "HANAI", GetColor(0, 0, 255));
}
