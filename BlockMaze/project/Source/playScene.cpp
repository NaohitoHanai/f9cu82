#include "playScene.h"
#include "../Library/sceneManager.h"
#include "DebugScreen.h"
#include <DxLib.h>
#include "Stage.h"

PlayScene::PlayScene()
{
	Stage* s = Instantiate<Stage>();
	SetDrawOrder(s, 10);
}

PlayScene::~PlayScene()
{
}

void PlayScene::Update()
{

	if (CheckHitKey(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TitleScene");
	}
	SceneBase::Update();
}

void PlayScene::Draw()
{
	SceneBase::Draw();
}
