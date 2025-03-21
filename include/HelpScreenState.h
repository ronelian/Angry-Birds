#pragma once

#include "State.h"
#include "Game.h"

class HelpScreenState : public State
{
public:
	HelpScreenState(std::shared_ptr<GameTools> gameTools);
	virtual ~HelpScreenState() = default;

	//virtual funcs
	virtual void processManeger()override;
	virtual void update()override;
	virtual void Draw()override;
	virtual void Resume()override {}

	//setters
	helpScreenCommand handleClick(const sf::Vector2f& mouse_loc);
	void helpManeger();
	void drawHelpScreen();
	void moveBetweenPages();

protected:
	void initilaize()override;

private:

	std::shared_ptr<GameTools> m_gameTools;
	sf::RectangleShape m_backButton;
	std::vector<sf::CircleShape> m_Buttons;
	sf::RectangleShape m_backGround;

	helpScreenCommand m_direction;
	helpScreenCommand m_mode;

	int m_currentInstructionPage;
	bool m_event;
};
