#pragma once
#include "Object3D.h"

class StageObject : public Object3D {
public:
	StageObject(const std::string& fileName, const VECTOR3& position, const VECTOR3& rotation, const VECTOR3& scale);
	~StageObject();
	void Draw() override;
	void PostDraw();
	int HitModel() { return hHitModel; }
private:
	int hHitModel;
};