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
	/// Ready���I����������ׂ�
	/// </summary>
	/// <returns>Ready���I�������true</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};