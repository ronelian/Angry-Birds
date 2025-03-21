#pragma once
#include <box2d/box2d.h>
#include <iostream>
#include "Objects.h"


void handleCollision(Objects& obj_1, Objects& obj_2);

class MyContactListener : public b2ContactListener
{
public:
	MyContactListener() = default;
	~MyContactListener() = default;

	void BeginContact(b2Contact* contact);
	//void EndContact(b2Contact* contact); <-we dont need

private:
};

