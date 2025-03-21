#pragma once
#include "Bird.h"


class RedBird: public Bird
{
public:
	RedBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr = {0,BIRD_HP,0});
	virtual ~RedBird() = default;

private:
};


