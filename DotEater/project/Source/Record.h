#pragma once
// Record.h

// classのプログラム
// データは、できるだけ、privateに書く
// データを外に見せたければ、関数を通して、値だけ返す
// 外から操作させる場合でも、直接変数に代入させない

// コンストラクターは、内部が正しく動くようにする
// メンバー変数を初期化

// デストラクターは、自分が消えるときに、後片付けをする
// newしているものがあれば、deleteする
// ロードしている素材（画像・モデル・音）があれば、Deleteする

class Record
{
public:
	Record() { x = 0; life = 500; }
	~Record() {}
	int GetX() { return x; } // 変数を見せるにはゲッター関数
	bool IsDead() { return life <= 0; } // ライフの変数は見せないけど、
	                                    // 知りたい情報を提供する
	void LifeMax() { life = 500; } // ライフを操作する関数
private:
	float x; // 変数はprivateに書いて、外から書き換えないようにする
	int life;
};