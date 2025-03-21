#include "MyContactListener.h"
#include <functional>
#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

#include "Ground.h"
#include "Rogatka.h"
#include "World.h"
#include "RedBird.h"
#include "YellowBird.h"
#include "BlueBird.h"
#include "BlackBird.h"
#include "Obstacle.h"
#include "CircularObstacle.h"


void MyContactListener::BeginContact(b2Contact* contact)
{
    b2Fixture* fixtureA = contact->GetFixtureA();
    b2Fixture* fixtureB = contact->GetFixtureB();

    // Get the bodies involved in the contact
    b2Body* bodyA = fixtureA->GetBody();
    b2Body* bodyB = fixtureB->GetBody();

    if (reinterpret_cast<World*>(bodyA->GetUserData().pointer) == nullptr ||
        reinterpret_cast<World*>(bodyB->GetUserData().pointer) == nullptr)
        return;

    Objects* first = reinterpret_cast<Objects*>(bodyA->GetUserData().pointer);
    Objects* second = reinterpret_cast<Objects*>(bodyB->GetUserData().pointer);


    handleCollision(*first, *second);
}

namespace {//begin namespace

//-------------HIT FUNCTIONS-----------

 void groundObstacle(Objects& ground, Objects& wood) {
     wood.setDamage(wood.getBodyMass()/2.f * wood.getBodyVelocity().LengthSquared());
}

void ObstacleGround(Objects& wood, Objects& ground) {
    groundObstacle(ground, wood);
}

void ObstacleObstacle(Objects& firstWood, Objects& SecondWood) {
    firstWood.setDamage(SecondWood.getBodyMass() * SecondWood.getBodyVelocity().LengthSquared());
    SecondWood.setDamage(firstWood.getBodyMass() * firstWood.getBodyVelocity().LengthSquared());
}

void birdObstacle(Objects& bird, Objects& obstacle) {
    static_cast<Bird&>(bird).gotHit();
    obstacle.setDamage(bird.getBodyMass() * bird.getBodyVelocity().LengthSquared());
    static_cast<Obstacle&>(obstacle).hitState();
}

void ObstacleBird(Objects& wood, Objects& bird) {
    birdObstacle(bird, wood);
}

void birdCircularObstacle(Objects& bird, Objects& obstacle) {
    static_cast<Bird&>(bird).gotHit();
    obstacle.setDamage(bird.getBodyMass() * bird.getBodyVelocity().LengthSquared());
    static_cast<CircularObstacle&>(obstacle).hitState();
}

void CircularObstacleBird(Objects& obstacle, Objects& bird) {
    birdObstacle(bird, obstacle);
}

void BirdGround(Objects& bird, Objects& ground) {
    if(!static_cast<Bird&>(bird).isOnRogatka())
        static_cast<Bird&>(bird).gotHit();
}

void GroundBird(Objects& ground, Objects& bird) {
    BirdGround(bird, ground);
}
//-----------END HIT FUNCTION------------

using HitFunctionPtr = std::function<void(Objects&, Objects&)>;
// typedef void (*HitFunctionPtr)(GameObject&, GameObject&);
using Key = std::pair<std::type_index, std::type_index>;
// std::unordered_map is better, but it requires defining good hash function for pair
using HitMap = std::map<Key, HitFunctionPtr>;

HitMap initializeCollisionMap()
{
    HitMap phm;
    phm[Key(typeid(Ground), typeid(RedBird))] = &GroundBird;
    phm[Key(typeid(RedBird), typeid(Ground))] = &BirdGround;

    phm[Key(typeid(Ground), typeid(BlueBird))] = &GroundBird;
    phm[Key(typeid(BlueBird), typeid(Ground))] = &BirdGround;

    phm[Key(typeid(Ground), typeid(YellowBird))] = &GroundBird;
    phm[Key(typeid(YellowBird), typeid(Ground))] = &BirdGround;

    phm[Key(typeid(Ground), typeid(BlackBird))] = &GroundBird;
    phm[Key(typeid(BlackBird), typeid(Ground))] = &BirdGround;

    phm[Key(typeid(Obstacle), typeid(Obstacle))] = &ObstacleObstacle;

    phm[Key(typeid(RedBird), typeid(Obstacle))] = &birdObstacle;
    phm[Key(typeid(Obstacle), typeid(RedBird))] = &CircularObstacleBird;

    phm[Key(typeid(YellowBird), typeid(Obstacle))] = &birdObstacle;
    phm[Key(typeid(Obstacle), typeid(YellowBird))] = &CircularObstacleBird;


    phm[Key(typeid(BlueBird), typeid(Obstacle))] = &birdObstacle;
    phm[Key(typeid(Obstacle), typeid(BlueBird))] = &CircularObstacleBird;


    phm[Key(typeid(BlackBird), typeid(Obstacle))] = &birdObstacle;
    phm[Key(typeid(Obstacle), typeid(BlackBird))] = &CircularObstacleBird;

    phm[Key(typeid(Ground), typeid(Obstacle))] = &groundObstacle;
    phm[Key(typeid(Obstacle), typeid(Ground))] = &ObstacleGround;

    // Circular Obstacle
    phm[Key(typeid(Obstacle), typeid(CircularObstacle))] = &ObstacleObstacle;
    phm[Key(typeid(CircularObstacle), typeid(Obstacle))] = &ObstacleObstacle;

    phm[Key(typeid(CircularObstacle), typeid(CircularObstacle))] = &ObstacleObstacle;

    phm[Key(typeid(RedBird), typeid(CircularObstacle))] = &birdCircularObstacle;
    phm[Key(typeid(CircularObstacle), typeid(RedBird))] = &ObstacleBird;

    phm[Key(typeid(YellowBird), typeid(CircularObstacle))] = &birdCircularObstacle;
    phm[Key(typeid(CircularObstacle), typeid(YellowBird))] = &ObstacleBird;


    phm[Key(typeid(BlueBird), typeid(CircularObstacle))] = &birdCircularObstacle;
    phm[Key(typeid(CircularObstacle), typeid(BlueBird))] = &ObstacleBird;

    phm[Key(typeid(BlackBird), typeid(CircularObstacle))] = &birdCircularObstacle;
    phm[Key(typeid(CircularObstacle), typeid(BlackBird))] = &ObstacleBird;

    phm[Key(typeid(Ground), typeid(CircularObstacle))] = &groundObstacle;
    phm[Key(typeid(CircularObstacle), typeid(Ground))] = &ObstacleGround;

    return phm;
}


HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
{
    static HitMap collisionMap = initializeCollisionMap();
    auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
    if (mapEntry == collisionMap.end())
    {
        return nullptr;
    }
    return mapEntry->second;
}

}//end namespace

void handleCollision(Objects& object1, Objects& object2) {

    auto collisionFunc = lookup(typeid(object1), typeid(object2));
    if (!collisionFunc)
        return;
    
    collisionFunc(object1, object2);
}

