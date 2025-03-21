#pragma once
#include "StaticObjects.h"

class Ground : public StaticObjects
{
public:
	Ground(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size = sf::Vector2f{ WINDOW_WIDTH, WINDOW_HEIGHT }, const arrData& arr = {0,0,0});
	 ~Ground() = default;

	//virtual funcs
	virtual void objectUpdate()override {}
	virtual void drawObject(sf::RenderWindow& window) override;
	virtual inline sf::Vector2f getPosition() const override{ return m_ground.getPosition(); };
	virtual void rotate(const int& x) override { ; };
	virtual void hitState() override { ; };

private:
	sf::RectangleShape m_ground;
	
	//init functions
	void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size);
	void initGraphicBody(const sf::Vector2f& size = { WINDOW_WIDTH, WINDOW_HEIGHT })override { ; };
	
};

