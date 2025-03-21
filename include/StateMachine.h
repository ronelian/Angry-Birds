#pragma once

#include "State.h"
#include <memory>
#include <stack>

class StateMachine
{
public:
	StateMachine();
	~StateMachine() = default;

	//states funcs
	void addState(std::unique_ptr<State>, bool);
	void removeState();
	void checkForUpdates();

	std::unique_ptr<State>& getCurrentState();

	void switchStates();
	void Switch();

private:
	std::unique_ptr<State> m_newGameState;
	std::stack<std::unique_ptr<State>> m_states;

	bool m_adding;
	bool m_removing;
	bool m_replacing;
	bool m_switch;
};

