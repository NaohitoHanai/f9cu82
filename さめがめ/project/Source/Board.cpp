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
			cells[y][x].dy = 0;
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
	static bool prev = true;
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		if (!prev) {
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
				Fall();
			}
		}
		prev = true;
	} else {
		prev = false;
	}

	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			if (cells[y][x].dy < 0) {
				cells[y][x].dy = 0;
			}else if (cells[y][x].dy > 0) {
				cells[y][x].dy -= fallSpeed;
			}
		}
	}
	fallSpeed += 2.2f;
}

void Board::Draw()
{
	for (int y = 0; y < cells.size(); y++) {
		for (int x = 0; x < cells[y].size(); x++) {
			int c = cells[y][x].color;
			if (c >= Red) {
				int dy = cells[y][x].dy;
				DrawRectGraph(x * 32, y * 32 - dy, c*32, 0, 32, 32,
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

void Board::Fall()
{
	for (int x = 0; x < cells[0].size(); x++) {
		int ysize = cells.size();
		int fall = 0;
		for (int y = ysize-1; y >= 1; y--) {
			if (cells[y][x].color == Wall)
				continue;
			if (cells[y][x].color == No) {
				fall++;
			} else if (fall > 0){
				cells[y + fall][x] = cells[y][x];
				cells[y + fall][x].dy += fall * 32;
				cells[y][x].color = No;
			}
		}
	}
	fallSpeed = 0.0f;
}
