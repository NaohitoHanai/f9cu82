#include "State.h"

State::State()
{
	exec.clear();
	current = nullptr;
	currentName = "";
}

State::~State()
{
}

void State::Update()
{
	if (current != nullptr) {
		current->Update();
	}
}

void State::Entry(std::string state, StateBase* func)
{
	exec.emplace(state, func);
}

void State::ChangeState(std::string state)
{
	if (currentName == state)
		return;
	if (current != nullptr) {
		current->Suspend();
	}
	current = exec[state];
	if (current != nullptr) {
		current->Resume();
	}
}
