#include "Coin.h"
#include "Player.h"

Coin::Coin(VECTOR pos)
{
	hModel = MV1LoadModel("data/models/Coin.mv1");
	position = pos;
	gotten = false;
}

Coin::~Coin()
{
}

void Coin::Update()
{
	Player* pl = FindGameObject<Player>();
	VECTOR pPos = pl->GetPosition(); // プレイヤーの足元の座標
	pPos += VGet(0,50,0); // コインと同じ高さにする

	if (gotten) {
		// 取られたので、プレイヤーに近づく
		// １．コインからプレイヤーに向かうベクトルを作る
		VECTOR v = pPos - position;
		// ２．そのベクトルの長さが5のものを作る（コインの移動ベクトル）
		v = VNorm(v) * 5.0f; // VNorm()はベクトルの長さを１にする関数
		// ３．コインの座標に加える
		position += v;
		// ４．コインとプレイヤーの距離が10以下になったらDestroyMe()
		float diff = VSize(pPos - position);
		if (diff < 10.0f) {
			DestroyMe();
		}
	} else {
		float diff = VSize(pPos - position);
		if (diff < 120.0f) { // コインに当たってる
			gotten = true;
		}
	}
}
