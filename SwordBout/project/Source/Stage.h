#pragma once
#include "Object3D.h"
class SphereCollider;

class Stage : public Object3D {
public:
	Stage(int number = 0);
	~Stage();
	struct ColliderRet {
		VECTOR3 VPush; // 垂直方向の押し出し
		VECTOR3 HPush; // 水平方向の押し出し
	};
	ColliderRet CollideSphere(const SphereCollider& base) const;
	bool CollideLine(const VECTOR& pos1, const VECTOR& pos2, VECTOR* hit = nullptr) const;
private:
	void ReadMappingData(std::string filename);
};