# pragma once


#include <SFML/Graphics.hpp>
#include<SFML/Audio.hpp>


#include "Macro.h"
#include "State.h"
#include "Game.h"



class MainMenuState : public State
{
public:
	MainMenuState(std::shared_ptr<GameTools>, bool);
	~MainMenuState() = default;

	//virtual funcs
	virtual void processManeger();
	virtual void update();
	virtual void Draw();
	virtual void Resume()override;

	//getters
	menuCommand handleClick(const sf::Vector2f& mouse_loc);
	void menuManeger();
	void drawMenu();

protected:
	void initilaize();

private:
	std::shared_ptr<GameTools> m_gameTools;
	std::vector<sf::RectangleShape> m_buttons;

	sf::CircleShape m_soundButton;
	sf::RectangleShape m_backGround;

	menuCommand m_mode;
	bool m_event;
	bool m_newAlloc; //give instraction if we need to allocate new level select state or not
};
