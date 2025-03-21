# pragma once

#include <SFML/Graphics.hpp>
#include "GameResources.h"

class State
{
public:
	State() = default;
	~State() = default;

	//virtual funcs
	virtual void processManeger() = 0;
	virtual void update() = 0;
	virtual void Draw() = 0;
	virtual void Resume() = 0;

	void soundButtonClicked(sf::CircleShape&);
	void setSoundTexture(sf::CircleShape&);

protected:
	virtual void initilaize() = 0;

private:


};