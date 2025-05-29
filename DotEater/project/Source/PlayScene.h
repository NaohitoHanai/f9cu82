#pragma once
#include "../Library/SceneBase.h"

/// <summary>
/// ゲームプレイのシーンを制御する
/// </summary>
class PlayScene : public SceneBase
{
public:
	PlayScene();
	~PlayScene();
	void Update() override;
	void Draw() override;
	bool CanPlay();
private:
	enum State { // ゲーム状態
		S_READY = 0,
		S_PLAY,
		S_TIMEUP,
		S_CLEAR,
	};
	State state;
};
