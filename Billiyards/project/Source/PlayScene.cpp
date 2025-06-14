#include "PlayScene.h"
#include <DxLib.h>
#include "Ball.h"

PlayScene::PlayScene()
{
	new Ball(1, VECTOR3(100, 200, 0));
	new Ball(3, VECTOR3(300, 300, 0));
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{
	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	DrawString(0, 0, "PLAY SCENE", GetColor(255, 255, 255));
	DrawString(100, 400, "Push [T]Key To Title", GetColor(255, 255, 255));
}
