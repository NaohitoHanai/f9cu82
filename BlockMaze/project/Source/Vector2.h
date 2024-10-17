#pragma once

struct VECTOR2 { // ç\ë¢ëÃ
	float x; // ç¿ïW
	float y;
	VECTOR2() { x = 0; y = 0; }
	VECTOR2(float _x, float _y) {
		x = _x; y = _y;
	}
};

float VSize(VECTOR2 v);

VECTOR2 VSub(VECTOR2 v1, VECTOR2 v2);

VECTOR2 VAdd(VECTOR2 v1, VECTOR2 v2);

VECTOR2 operator +(VECTOR2 v1, VECTOR2 v2);

VECTOR2 VScale(VECTOR2 v, float s);

VECTOR2 VNorm(VECTOR2 v);

bool CircleHit(VECTOR2 obj1, VECTOR2 obj2, float r);