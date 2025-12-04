#pragma once
#include <DxLib.h>

 namespace Input {
	void Init();
	void Update();
	bool IsKeyPress(int key);
	bool IsKeyOnTrig(int key);

	bool IsMousePress(int key);
	bool IsMouseOnTrig(int key);

	const POINT& MousePosition();
};