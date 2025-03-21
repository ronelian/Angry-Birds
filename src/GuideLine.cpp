#include "GuideLine.h"

GuideLine& GuideLine::getInstance()
{
	static GuideLine guideline;
	return guideline;
}


void GuideLine::initPhysicBody()
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.linearDamping = 0.7f;
    bodyDef.position.Set(ROGATKA_X / SCALE, ROGATKA_Y - 50.f / SCALE);
    b2Body* body = m_world->getWorld()->CreateBody(&bodyDef);
    m_bodies.push_back(body);

    // Create Box2D circle shape
    b2CircleShape shape;
    shape.m_radius = 20.f / SCALE;

    b2FixtureDef fixtureDef;
    fixtureDef.shape = &shape;
    fixtureDef.density = BIRD_HP * 0.1f;
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);
}


void GuideLine::initGraphicBody()
{
    m_guideline.emplace_back();
    m_guideline.back().setFillColor(sf::Color::Black);
    m_guideline.back().setRadius(5.f);
    m_guideline.back().setOrigin(2.5f, 2.5f);
 
}

void GuideLine::setWorld(std::shared_ptr<World> world)
{
    m_world = world;
}

void GuideLine::drawGuideLine(sf::RenderWindow& window)
{
    if (m_timer.getElapsedTime() <= sf::seconds(0.1f)) return;
    for (size_t i = 0; i < m_bodies.size() ; i++)
    {
        m_guideline.at(i).setPosition(m_bodies.at(i)->GetPosition().x * SCALE, m_bodies.at(i)->GetPosition().y * SCALE);
        window.draw(m_guideline.at(i));
    }
}

void GuideLine::reset()
{
    for (auto& ea : m_bodies)
        m_world->getWorld()->DestroyBody(ea);
    
    m_bodies.clear();
    m_guideline.clear();
    m_timer.restart();
    m_engage = false;
    
}

void GuideLine::setPosition(const sf::Vector2f& pos)
{
    if (!m_engage) // first pos aiming
    {
        m_engage = true;
        m_birdPos = pos;
        m_timer.restart();
    }

    if (pos != m_birdPos) // if bird moved we reset
    {
        reset();
        return;
    }
       

    b2Vec2 dir{ (ROGATKA_X - pos.x) * 25.f / SCALE, (ROGATKA_Y - 50.f - pos.y) * 25.f / SCALE };

    initPhysicBody();
    initGraphicBody();

    m_bodies.back()->SetTransform({ pos.x / SCALE, pos.y / SCALE }, 0);
    m_bodies.back()->SetLinearVelocity(dir);

    if (m_bodies.size() >= 40 && m_timer.getElapsedTime() >= sf::seconds(1.5f)) 
        reset();

}
