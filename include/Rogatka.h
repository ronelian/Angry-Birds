#pragma once

#include "StaticObjects.h"


class Rogatka:public StaticObjects
{
public:
	Rogatka(std::shared_ptr<World> world, const sf::Vector2f& position = {ROGATKA_X, ROGATKA_Y}, const sf::Vector2f& size = sf::Vector2f{ 15.f, 80.f }, arrData arr = { 1,0,0 });
	virtual ~Rogatka() = default;

	//virtual funcs
	virtual void objectUpdate()override {}
	virtual virtual void drawObject(sf::RenderWindow& window);
	virtual inline sf::Vector2f getPosition() const override { return m_rogatka.getPosition(); };
	virtual void rotate(const int& x) override { ; };
	virtual void hitState() override { ; };

	//setters
	void ignoreRogatka();
	void resetRogatka();

	//getters
	void drawSit(sf::RenderWindow& w, const sf::Vector2f& begin , const sf::Vector2f& pos, const float& angle);

private:
	sf::RectangleShape m_rogatka;
	sf::RectangleShape m_sit;
	sf::Vector2f m_rogatkaSize; //size of the rogatka;
	
	int m_textureIndex;

	// private funcs
	virtual void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) ;
	virtual void initGraphicBody(const sf::Vector2f& size) ;
	void setObjOnRogatka(const sf::Vector2f& pos, const float& angle);
};

