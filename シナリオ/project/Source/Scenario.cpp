#include "Scenario.h"
#include <assert.h>

Scenario::Scenario()
{
	csv = new CsvReader("data/csv/SCN1_1.csv");
	assert(csv->GetLines()>0);

	bg = new BG();
	for (int c = 0; c < 2; c++) {
		chara[c] = new Chara();
	}

	readLine = 1;
}

Scenario::~Scenario()
{
}

void Scenario::Update()
{
	std::string com = csv->GetString(readLine, 1);
	// コマンドを実行
	if (com == "BGSET") {
		bg->Set(csv->GetString(readLine, 3));
	}
	if (readLine < csv->GetLines()-1)
		readLine++;
}

void Scenario::Draw()
{
}
