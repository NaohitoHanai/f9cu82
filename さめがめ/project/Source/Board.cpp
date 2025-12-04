#include "Board.h"

Board::Board()
{
	cells.resize(10);
	for (int y = 0; y < cells.size(); y++) {
		cells[y].resize(15);
		for (int x = 0; x < cells[y].size(); x++) {
			if (x == 0 || y == 0 || y == cells.size()-1 || x == cells[y].size()-1) {
				cells[y][x].color = Wall;
			} else {
				cells[y][x].color = rand() % (Wall-Red);
			}
		}
	}

	hImage = LoadGraph("data/puyo.png");
}

Board::~Board()
{
}

void Board::Update()
{
	int x, y;
	GetMousePoint(&x, &y);
	select.x = x / 32;
	select.y = y / 32;
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (select.y >= cells.size())
			return;
		if (select.x >= cells[select.y].size())
			return;
		if (cells[select.y][select.x].color == Wall)
			return;
		if (cells[select.y][select.x].color == No)
			return;
		Clear();
		if (Check(select.x, select.y) > 1) {
			Erase();
		}
	}
}

void Board::Draw()
{
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			int c = cells[y][x].color;
			if (c >= Red) {
				DrawRectGraph(x * 32, y * 32, c*32, 0, 32, 32,
					hImage, TRUE);
				if (cells[y][x].erase) {
					DrawString(x*32, y*32,"E",
									GetColor(255,255,255));
				}
			}
		}
	}
	DrawBox(select.x*32, select.y*32, 
					(select.x+1)*32, (select.y+1)*32,
					GetColor(255,255,255), FALSE);
}

void Board::Clear()
{
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			cells[y][x].erase = false;
		}
	}
}

int Board::Check(int x, int y)
{
	int num = 1; // Ž©•ª
	cells[y][x].erase = true;
	int col = cells[y][x].color; // Ž©•ª‚ÌF
	if (cells[y][x - 1].color == col && !cells[y][x - 1].erase) {
		num += Check(x - 1, y);
	}
	if (cells[y][x + 1].color == col && !cells[y][x + 1].erase) {
		num += Check(x + 1, y);
	}
	if (cells[y - 1][x].color == col && !cells[y - 1][x].erase) {
		num += Check(x, y - 1);
	}
	if (cells[y + 1][x].color == col && !cells[y + 1][x].erase) {
		num += Check(x, y + 1);
	}
	return num;
}

void Board::Erase()
{
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			if (cells[y][x].erase)
				cells[y][x].color = No;
		}
	}

}
