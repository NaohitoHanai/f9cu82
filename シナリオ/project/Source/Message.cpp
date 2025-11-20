#include "Message.h"

Message::Message()
{
	text = "";
	len = 0;
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
	std::string st = text.substr(0, len); //0”Ô–Ú‚©‚ç2•¶Žš
	SetFontSize(30);
	DrawString(200, 600, st.c_str(), GetColor(255,255,255));
	SetFontSize(s);
}

bool Message::SetText(std::string txt)
{
	len += 2;
	if (len >= txt.length())
		len = txt.length();
	text = txt;
	return false;
}
