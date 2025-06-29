#pragma once
#include "Object3D.h"

class ReadyGo : public Object3D
{
public:
	ReadyGo();
	~ReadyGo();
	void Update();
	void Draw();
	/// <summary>
	/// Readyが終わったか調べる
	/// </summary>
	/// <returns>Readyが終わったらtrue</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};