#pragma once
#include "Object3D.h"
#include <vector>

class Stage : public Object3D
{
public:
	Stage();
	~Stage();
	void Draw() override;
private:
	std::vector<std::vector<int>> maps;
};