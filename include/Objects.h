#pragma once

#include <SFML/Graphics.hpp>
#include <box2d/box2d.h>

#include "Macro.h"
#include "GameResources.h"
#include "ObjectFactory.h"
#include "World.h"


class Objects
{
public:
	Objects(std::shared_ptr<World> world, const int& hp = 100) : m_hp{ hp }, m_body{ nullptr }, m_world{world} {}

	virtual ~Objects() {
		if(m_body)
			m_world->getWorld()->DestroyBody(m_body); 
	};

	//virtual funcs
	virtual void objectUpdate() = 0;
	virtual void drawObject(sf::RenderWindow& window) = 0;
	virtual sf::Vector2f getPosition() const = 0;
	virtual void rotate(const int& x) = 0;

	//getters
	int getHp() const { return m_hp; }
	const b2Vec2& getBodyVelocity() const { return m_body->GetLinearVelocity(); };
	float getBodyMass() const { return m_body->GetMass(); };

	//setters
	void setDamage(const int &damage) { m_hp -= damage; }
	void setHp(int hp) { m_hp = hp; };
	void rotateBody() { m_body->SetTransform(m_body->GetPosition(), m_body->GetAngle() + b2_pi / 2.0f); };

	

protected:
	b2Body* m_body;

	//protected funcs
	virtual void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) = 0;
	virtual void initGraphicBody(const sf::Vector2f& size) = 0;

private:
	int m_hp;
	std::shared_ptr<World> m_world;

};

