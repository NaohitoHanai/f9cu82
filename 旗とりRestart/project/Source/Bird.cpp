#include "Bird.h"
#include "config.h"
#include "Player.h"
#include "Stone.h"

Bird::Bird()
{
	hImage = LoadGraph("data/image/mob.png");
	position.x = rand()%1000;
	position.y = rand()%700;
	speed.x = 0.0;
	speed.y = 0.0f;
	patternX = 0;
	patternY = 0;
	frameCounter = 0;

	timer = 60;
	attacking = false;

	dead = false;
}

Bird::~Bird()
{
	DeleteGraph(hImage);
}

void Bird::Update()
{
	if (dead) {
		deadCounter++;
		if (deadCounter >= 30) {
			DestroyMe();
		}
		return;
	}
	if (attacking) { // 突入しているなら
		Player* player = FindGameObject<Player>();
		VECTOR2 to = VSub(player->position, position); // 相手へのベクトル
		to = VNorm(to); // toベクトルの長さを１にする
		// positionに加える
//		position = VAdd(position, VScale(to, 2.0f));
		position = position + VScale(to, 2.0f);

		VECTOR2 d = VSub(player->position, position);// 自分からプレイヤーへのベクトルを求めて
		if (VSize(d)<120) { // 長さが120以下になったら
			attacking = false; // 突入をやめて、水平移動にする
		}
	}
	else {
		timer -= 1;
		if (timer == 0) {
			attacking = true;
			timer = rand() % (5 * 60) + 60;
		}
		position.x -= 0.5f;
		if (position.x < -64) {
			position.x = SCREEN_WIDTH;
			position.y = rand() % 700;
		}
		frameCounter = (frameCounter + 1) % 15;
		if (frameCounter == 0) {
			patternY = (patternY + 1) % 4;
		}
	}
	// 石と当たり判定をする
	std::list<Stone*> stones = FindGameObjects<Stone>(); // 全部の石
	for (Stone* st : stones) { // stに１つずつ石のポインターが入る
		// ①石の当たり判定の中心座標を求める
		VECTOR2 sCenter;
		sCenter.x = st->position.x + 8;
		sCenter.y = st->position.y + 8;
		// ②鳥の当たり判定の中心座標を求める
		VECTOR2 bCenter;
		bCenter.x = position.x + 32;
		bCenter.y = position.y + 32;
		// ①と②の円の当たり判定をする
		if (CircleHit(sCenter, bCenter, 32 + 8)) {
			dead = true;
			deadCounter = 0;
			patternY = 4;
			st->DestroyMe();
		}
	}
}

void Bird::Draw()
{
	DrawRectGraph(position.x, position.y, patternX * 64, patternY * 64, 64, 64, hImage, TRUE);
	DrawCircle(position.x+32, position.y+32, 30, GetColor(255, 0, 0), 0);
}
