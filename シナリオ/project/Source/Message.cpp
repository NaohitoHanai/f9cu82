#include "Message.h"

Message::Message()
{
	text = "";
	len = 0;
	textInterval = 0;
	waitButton = false;
	r = 0;
	speaker = "";
}

Message::~Message()
{
}

void Message::Update()
{
}

void Message::Draw()
{
	int s = GetFontSize();
	std::string st = text.substr(0, len); //0番目から2文字
	SetFontSize(30);
	DrawString(200, 550, speaker.c_str(), GetColor(255,255,255));
	DrawString(200, 600, st.c_str(), GetColor(255,255,255));
	SetFontSize(s);

	if (waitButton) {
		SetFontSize(30);
		r += DX_PI / 30;
		y = abs(sin(r)) * 10;
		DrawString(800, 600+y, "▼", GetColor(255, 255, 255));
		DrawString(800, 600+10, "＿", GetColor(255, 255, 255));
		SetFontSize(s);
	}
}

bool Message::SetText(std::string txt)
{
	// waitButtonがtrueなら、ボタンを押した時にtrueを返す
	if (waitButton) {
		if (CheckHitKey(KEY_INPUT_SPACE)) {
			len = 0;
			textInterval = 0;
			waitButton = false;
			return true;
		}
		return false;
	}
	if (textInterval == 0) {
		std::string letter = txt.substr(len, 2); //最後の１文字
		if (letter == "▽") {
			// ここでボタン待ち
			waitButton = true;
		} else if (letter == "＞") {
			speaker = txt;
			return true;
		} else {
			if (txt[len] == '\n')
				len += 1;
			else
				len += 2;
		}
		textInterval = 10;
	} else {
		textInterval -= 1;
	}
	if (len >= txt.length())
		len = txt.length();
	text = txt;
	return false;
}
