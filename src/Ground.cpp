#include "Ground.h"


Ground::Ground(std::shared_ptr<World> world , const sf::Vector2f& position, const sf::Vector2f& size, const arrData& arr)
    : StaticObjects(world) {
    initPhysicBody(world, position, size);
    initGraphicBody();
}


void Ground::initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) {
    /* NEED TO CHANGE TO CHAIN*/
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(size.x/2.f/SCALE, (size.y - 60.f)/ SCALE);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->getWorld()->CreateBody(&bodyDef);

    // Create Box2D ground shape
    b2PolygonShape groundshape;
    groundshape.SetAsBox(size.x / 2.f / SCALE, 25.f / SCALE); /* CHANGER 25 TO SIZE.Y */
     
    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}


void Ground::drawObject(sf::RenderWindow &window)
{
    window.draw(m_ground);
}

//to "register" the object in the Factory
static auto registerItGround = ObjectFactory<StaticObjects>::instance().registerType(
    "ground",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr) -> std::unique_ptr<StaticObjects>
    {
        return std::make_unique<Ground>(world, position, size, arr);
    }
);