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
	/// Ready‚ªI‚í‚Á‚½‚©’²‚×‚é
	/// </summary>
	/// <returns>Ready‚ªI‚í‚Á‚½‚çtrue</returns>
	bool TimeEnd();
private:
	int hReady;
	int hGo;
	float timer;
};