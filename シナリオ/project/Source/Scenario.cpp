#include "Scenario.h"
#include <assert.h>
#include "Fade.h"

Scenario::Scenario()
{
	csv = new CsvReader("data/csv/SCN1_1.csv");
	assert(csv->GetLines()>0);

	bg = new BG();
	for (int c = 0; c < 2; c++) {
		chara[c] = new Chara();
	}
	message = new Message();

	readLine = 1;
}

Scenario::~Scenario()
{
}

void Scenario::Update()
{
	std::string mes = csv->GetString(readLine, 0);
	if (mes != "") {
		if (message->SetText(mes)) {
			if (readLine < csv->GetLines() - 1)
				readLine++;
		}
		return;
	}
	std::string com = csv->GetString(readLine, 1);
	// コマンドを実行
	if (com == "BGSET") {
		bg->Set(csv->GetString(readLine, 3));
	}
	if (com == "FADEOUT") {
		Fade* fade = FindGameObject<Fade>();
		fade->FadeOut(csv->GetString(readLine, 3), csv->GetFloat(readLine, 4));
	}
	if (com == "FADEIN") {
		Fade* fade = FindGameObject<Fade>();
		fade->FadeIn(csv->GetString(readLine, 3), csv->GetFloat(readLine, 4));
	}
	if (com == "WAIT_FADE") {
		Fade* fade = FindGameObject<Fade>();
		if (fade->Finished() == false)
			readLine--;
	}
	if (com == "CHARA_READ") {
		int id = csv->GetInt(readLine, 2);
		chara[id]->Set(csv->GetString(readLine, 3));
	}
	if (com == "CHARA_MOVE") {
		int id = csv->GetInt(readLine, 2);
		int x = csv->GetInt(readLine, 3);
		float t = csv->GetFloat(readLine, 4);
		chara[id]->Move(x, 0, t);
	}
	if (com == "WAIT_CHARA") {
		int id = csv->GetInt(readLine, 2);
		if (chara[id]->Finished() == false) {
			readLine--;
		}
	}
	if (readLine < csv->GetLines()-1)
		readLine++;
}

void Scenario::Draw()
{
}
