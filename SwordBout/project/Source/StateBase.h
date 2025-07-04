#pragma once
class GameObject;

class StateBase {
public:
	StateBase(GameObject* base) {baseObject = base;}
	virtual ~StateBase() {}
	virtual void Resume() {} // 再開
	virtual void Update() {} // 更新
	virtual void Suspend() {} // 一時停止
protected:
	GameObject* baseObject;
	template<class C>
	C* GetBase() {
		return dynamic_cast<C*>(baseObject);
	}
};