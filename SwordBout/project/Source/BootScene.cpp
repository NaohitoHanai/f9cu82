#include "BootScene.h"
#include "PadInput.h"

BootScene::BootScene()
{
	new PadInput(DX_INPUT_PAD1);
}

BootScene::~BootScene()
{
}

void BootScene::Update()
{
	SceneManager::ChangeScene("TITLE"); // ‹N“®‚ªI‚í‚Á‚½‚çTitle‚ğ•\¦
}

void BootScene::Draw()
{
}
