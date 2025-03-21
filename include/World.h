#pragma once

#include <memory>
#include <array>
#include <box2d/box2d.h>


#include "Macro.h"
#include "GameResources.h"

enum  Position { Left, Right };

class World 
{
public:
	World();
	~World() = default;

	//getters
	b2World* getWorld(){ return m_world.get();}
	void step(const float& timestep,const int32& velocity,const int32& positionIteration);

private:
	//set the world frame
	std::array<b2Body*, 2> m_worldFrame;

	std::unique_ptr <b2World> m_world;

	//init functions
	void setFrame();
	b2Body* setCorner(Position position);
};

