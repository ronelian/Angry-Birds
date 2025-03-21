#include "StateMachine.h"

StateMachine::StateMachine()
	:m_adding(false), m_removing(false), m_replacing(false), m_switch(false)
{}

void StateMachine::addState(std::unique_ptr<State> newState, bool replacing)
{
	m_adding = true;
	m_replacing = replacing;
	m_newGameState = std::move(newState);
}

void StateMachine::removeState()
{
	m_removing = true;
}

void StateMachine::checkForUpdates()
{
	if (m_adding)//if need to add new state
	{
		if (!m_states.empty())//check the states not empty
		{
			if (m_replacing)//replace the current state with the new one
			{
				m_states.top().release();
				m_states.pop();
			}
		}
		m_states.push(std::move(m_newGameState));
		m_adding = false;
	}

	if (m_removing && !m_states.empty())
	{
		m_states.top().release();
		m_states.pop();
		m_states.top()->Resume();
		m_removing = false;
	}
	if (m_switch)
	{
		Switch();
		m_switch = false;
	}
}

std::unique_ptr<State>& StateMachine::getCurrentState() 
{
	return m_states.top();
}

void StateMachine::switchStates()
{
	m_switch = true; 
}

void StateMachine::Switch()
{
	//move the pointeres and clear stack
	std::unique_ptr<State> wasTop = std::move(m_states.top());
	m_states.pop();
	std::unique_ptr<State> wasBack = std::move(m_states.top());
	m_states.pop();

	//insert in new order
	m_states.push(std::move(wasTop));
	m_states.push(std::move(wasBack));
	
	//resume the operation the state which was in the back
	m_states.top()->Resume();
}