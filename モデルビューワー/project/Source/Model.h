#pragma once
#include "Object3D.h"

class Model : public Object3D
{
public:
	Model();
	~Model();
	void Update() override;
};