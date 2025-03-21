#pragma once

#include "Bird.h"

enum BirdState {
	normal,
	split
};


class BlueBird : public Bird
{
public:
	BlueBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr = {2,BIRD_HP,0});
	virtual ~BlueBird() = default;

	//virtual funcs
	virtual void handleEvent(sf::Event& event, const sf::Vector2f& mouse)override;
	virtual void objectUpdate()override;
	virtual void drawObject(sf::RenderWindow& window)override;

	//setters
	inline void setEnable() { m_body->SetEnabled(true); };

private:
	std::array<std::unique_ptr<BlueBird>,2> m_split;
	std::shared_ptr<World> m_world;
	bool isSplit;

	BirdState m_state;

	//private funcs
	void setBodySize();
};
