#pragma once
// Message.h
#include "../Library/GameObject.h"

class Message : public GameObject
{
public:
	Message();
	~Message();
	void Update() override;
	void Draw() override;
	bool SetText(std::string txt);
private:
	std::string text;
	int len; // 文字列表示の長さ
	int textInterval; // 1文字の時間
	bool waitButton; // ボタン待ち
	int y;
	float r;
	std::string speaker; // 話している人
};