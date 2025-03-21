#pragma once

#include <vector>
#include "World.h"

class GuideLine
{
public:
	
	static GuideLine& getInstance();
	GuideLine(const GuideLine&) = delete; //disable copy constructor
	GuideLine operator=(const GuideLine&) = delete; //disable assimenget operator

	//setters
	void setWorld(std::shared_ptr<World> world);
	void drawGuideLine(sf::RenderWindow& window);
	void reset();
	void setPosition(const sf::Vector2f& pos);

private:
	//private constructor and destructor
	GuideLine() : m_timer{}, m_birdPos{ ROGATKA_X, ROGATKA_Y - 50.f }, m_engage{false} { ; };
	~GuideLine() = default;

	//private memebrs
	std::vector<b2Body*> m_bodies;
	std::vector<sf::CircleShape> m_guideline;

	//for guideline indication
	sf::Clock m_timer;
	sf::Vector2f m_birdPos;
	bool m_engage;

	std::shared_ptr<World> m_world;
	

	//private funcs
	void initPhysicBody();
	void initGraphicBody();
};

