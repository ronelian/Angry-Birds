#pragma once

#include "StaticObjects.h"


class Obstacle :public StaticObjects
{
public:
	Obstacle(std::shared_ptr<World> world, const sf::Vector2f &position, const sf::Vector2f& size, arrData arr);
	virtual ~Obstacle() = default;

	//virtual funcs
	virtual void objectUpdate() override;
	virtual void drawObject(sf::RenderWindow& window) override;
	virtual inline sf::Vector2f getPosition() const override { return m_obstacle.getPosition(); }
	virtual inline void rotate(const int& x) override { this->rotateBody(); };
	virtual void hitState() override;

private:
	sf::RectangleShape m_obstacle;

	bool m_hit;
	int m_GameIndex;
	int m_halfHp;
	
	// Private funcs:
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& postion, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size)override;
};

