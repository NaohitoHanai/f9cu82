#include "PlayScene.h"
#include "Screen.h"
#include <vector>

struct Point { // １つの点の情報
	VECTOR3 pos;// 座標
	bool selected;
	unsigned int color;
};
Point points[100];

struct DragPoint {
	int x, y;
};
std::vector<DragPoint> drags;
bool drag;

PlayScene::PlayScene()
{
	for (auto& p : points)
	{
		p.pos.x = rand() % Screen::WIDTH;
		p.pos.y = rand() % Screen::HEIGHT;
		p.pos.z = 0;
		p.selected = true;
		p.color = GetColor(255,0,0);
	}
	drag = false;
	drags.clear();
}

PlayScene::~PlayScene()
{
}

bool CrossLine(VECTOR3 p1, VECTOR3 p2, VECTOR3 s1, VECTOR3 s2)
{
	VECTOR cr1 = VCross(p2 - p1, s1 - p1);
	VECTOR cr2 = VCross(p2 - p1, s2 - p1);
	if (cr1.z * cr2.z >= 0)
		return false;

	VECTOR cr3 = VCross(s2 - s1, p1 - s1);
	VECTOR cr4 = VCross(s2 - s1, p2 - s1);
	if (cr3.z * cr4.z >= 0)
		return false;

	// cr1.zとcr2.zの符号が逆、かつ、cr3.zとcr4.zの符号が逆ならtrue
	return true;
}

void PlayScene::Update()
{
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		DragPoint p;
		GetMousePoint(&p.x, &p.y);
		if (not drag) {
			drags.clear();
			drags.push_back(p);
			drag = true;
		} else {
			DragPoint last = *drags.rbegin(); // 最後の点
			int x = last.x-p.x;
			int y = last.y-p.y;
			if (x * x + y * y >= 100) { // 10ドット動いた
				drags.push_back(p);
			}
		}
	} else {
		if (drag) {
			DragPoint pos = *drags.begin();
			drags.push_back(pos);
			drag = false;

		}
	}
	if (Input::IsKeyOnTrig(KEY_INPUT_C))
	{
		//全ての点が、dragの内側にあるか調べる
		for (auto& p : points) {
			bool inside = false;
			for (int i = 0; i < drags.size() - 1; i++) {
				DragPoint d1 = drags[i];
				DragPoint d2 = drags[i + 1];
				VECTOR3 p1 = p.pos;
				VECTOR3 p2 = VECTOR3(0, 0, 0);
				if (CrossLine(p1, p2, VECTOR3(d1.x, d1.y, 0), VECTOR3(d2.x, d2.y, 0))) {
					inside = !inside;
				}
			}
			p.selected = inside;
		}
	}
	if (Input::IsKeyOnTrig(KEY_INPUT_T)) {
		SceneManager::ChangeScene("TITLE");
	}
}

void PlayScene::Draw()
{
	for (auto& p : points)
	{
		DrawCircle(p.pos.x, p.pos.y, 5, p.color);
		if (p.selected) {
			DrawCircle(p.pos.x, p.pos.y, 5, GetColor(255, 255, 255), 0);
		}
	}
	if (drags.size() >= 2) {
		DragPoint p = drags[0];
		for (auto d : drags) {
			DrawLine(p.x, p.y, d.x, d.y, GetColor(255,255,255));
			p = d;
		}
	}

	DrawString(0, 0, "PLAY SCENE", COL_WHITE);
	DrawString(100, 400, "Push [T]Key To Title", COL_WHITE);
}
