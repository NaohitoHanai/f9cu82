#include "GoalText.h"

GoalText::GoalText()
{
}

GoalText::~GoalText()
{
}

void GoalText::Update()
{
}

void GoalText::Draw()
{
	DrawString(200, 200, "GOAL", GetColor(255, 255, 255));
}
