#include "Player.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawRectGraph(0, 0, 0, 0, 64, 64, hImage, TRUE);
}
