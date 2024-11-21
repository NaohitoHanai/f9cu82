#include "GoalText.h"
#include "../Library/time.h"

GoalText::GoalText()
{
	timer = 0.0f;
}

GoalText::~GoalText()
{
}

int score = 100;

void GoalText::Update()
{
	timer += Time::DeltaTime();
	if (timer >= 2.5f) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			SceneManager::ChangeScene("TitleScene");
		}
	}
}

void GoalText::Draw()
{
	int size = GetFontSize();

	SetFontSize(50);
	DrawString(200, 200, "GOAL", GetColor(255, 255, 127));
	if (timer >= 1.0f) {
		SetFontSize(25);
		DrawFormatString(200, 300, GetColor(255, 255, 255),
			"SCORE.....%6d", score);
	}
	if (timer >= 2.0f) {
		DrawString(200, 500, "PUSH SPACE KEY", GetColor(255,255,255));
	}
	SetFontSize(size);
}



