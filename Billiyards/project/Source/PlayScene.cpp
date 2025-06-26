#include "PlayScene.h"
#include <DxLib.h>
#include "Ball.h"
#include "BallManager.h"

PlayScene::PlayScene()
{
	new Ball(1, VECTOR3(100, 200, 0));
	new Ball(3, VECTOR3(300, 300, 0));
	new Ball(4, VECTOR3(500, 400, 0));
	new Ball(5, VECTOR3(200, 3500, 0));
	new Ball(16, VECTOR3(500, 500, 0));
	new BallManager();
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
