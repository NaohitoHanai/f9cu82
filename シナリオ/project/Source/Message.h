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
	int len; // •¶Žš—ñ•\Ž¦‚Ì’·‚³
};