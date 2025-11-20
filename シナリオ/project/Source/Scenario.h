#pragma once
//Scenario.h
#include "../Library/GameObject.h"
#include "CsvReader.h"
#include "BG.h"
#include "Chara.h"
#include "Message.h"

class Scenario : public GameObject
{
public:
	Scenario();
	~Scenario();
	void Update() override;
	void Draw() override;
private:
	CsvReader* csv;
	int readLine; // ç°é¿çsíÜÇÃçs
	BG* bg;
	Chara* chara[2];
	Message* message;
};
