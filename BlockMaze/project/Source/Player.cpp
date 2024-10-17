#include "Player.h"

Player::Player()
{
	hImage = LoadGraph("data/image/chara.png");
	position.x = 0;
	position.y = 0;
	
}

Player::~Player()
{
}

void Player::Update()
{
}

void Player::Draw()
{
	DrawRectGraph(position.x, position.y, 0, 0, 40, 40, hImage, TRUE);
}
