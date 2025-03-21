#pragma once

#include "State.h"
#include "Game.h"

class TransitionScreens : public State
{
public:
	TransitionScreens(std::shared_ptr<GameTools>, const TransitionScreen&);
	~TransitionScreens() = default;

	//virtual funcs
	virtual void processManeger()override;
	virtual void update()override;
	virtual void Draw()override;
	virtual void Resume()override {}

protected:
	void initilaize();

private:
	sf::Clock m_stateClock;
	float m_stateTimeLimit;

	std::shared_ptr<GameTools> m_gameTools;
	sf::RectangleShape m_TransitionScreen;
	TransitionScreen m_texture;
};

