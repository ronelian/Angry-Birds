#pragma once

#include "StaticObjects.h"


class CircularObstacle :public StaticObjects
{
public:
	CircularObstacle(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size,const arrData& arr);
	virtual ~CircularObstacle() = default;

	//virtual funcs
	virtual void objectUpdate() override;
	virtual void drawObject(sf::RenderWindow& window) override;
	virtual inline sf::Vector2f getPosition() const override { return m_obstacle.getPosition(); }
	virtual inline void rotate(const int& x) override { this->rotateBody(); };
	virtual void hitState() override;

private:
	sf::CircleShape m_obstacle;

	bool m_hit;
	int m_textureIndex;
	int m_halfHp;

	// Private funcs:
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& postion, const sf::Vector2f& size)override;
	void initGraphicBody(const sf::Vector2f& size)override;
};

