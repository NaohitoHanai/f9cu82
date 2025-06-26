#pragma once
#include "Object3D.h"
#include <map>
#include "StateBase.h"

class State {
public:
	State();
	~State();
	void Update();
	void Entry(std::string state, StateBase* func);
	void ChangeState(std::string state);
private:
	std::map<std::string, StateBase*> exec;
	std::string currentName;
	StateBase* current;
};