#include "Rogatka.h"

Rogatka::Rogatka(std::shared_ptr<World> world,const sf::Vector2f& position, const sf::Vector2f& size, arrData arr)
    : StaticObjects(world), m_textureIndex{arr.at(0)} {
    initPhysicBody(world, position, size);
    initGraphicBody(size);
    m_rogatkaSize = m_rogatka.getSize();
}

void Rogatka::initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size) {
    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.position.Set(position.x  /  SCALE, (position.y) / SCALE);
    bodyDef.userData.pointer = reinterpret_cast<uintptr_t>(this);
    m_body = world->getWorld()->CreateBody(&bodyDef);

    b2PolygonShape groundshape;
    groundshape.SetAsBox(size.x/2 / SCALE, size.y / 2.f / SCALE);

    // Create Box2D fixture definition
    b2FixtureDef fixtureDef;
    fixtureDef.shape = &groundshape;
    fixtureDef.friction = 0.5f;
    m_body->CreateFixture(&fixtureDef);
}


void Rogatka::initGraphicBody(const sf::Vector2f& size) {
    b2Vec2 position = m_body->GetPosition();
    float angle = m_body->GetAngle();
    m_rogatka.setTexture(&GameResources::getInstance().getRogatkaTexture(m_textureIndex));
    m_rogatka.setSize(sf::Vector2f(size.x*8, size.y*2));
    m_rogatka.setOrigin(m_rogatka.getSize().x / 2.f, m_rogatka.getSize().y / 2.f);
    m_rogatka.setPosition(position.x * SCALE, position.y * SCALE);
    m_rogatka.setRotation(angle * size.y*3 / b2_pi);

    m_sit.setTexture(&GameResources::getInstance().getRogatkaTexture(1));
    m_sit.setSize(sf::Vector2f(30.f , 50.f));
    m_sit.setOrigin(m_sit.getSize().x / 2.f , m_sit.getSize().y / 2.f);
    
}

void Rogatka::setObjOnRogatka(const sf::Vector2f &pos,const float &angle)
{
    m_sit.setPosition(pos);
    m_sit.setRotation(angle);
}


void Rogatka::drawObject(sf::RenderWindow& window) {

    window.draw(m_rogatka);
}

void Rogatka::ignoreRogatka() {
    m_body->SetEnabled(false);
}
void Rogatka::resetRogatka() {
    m_body->SetEnabled(true);
}

void Rogatka::drawSit(sf::RenderWindow& w, const sf::Vector2f& begin, const sf::Vector2f& pos, const float& angle)
{
    setObjOnRogatka(pos, angle);
    w.draw(m_sit);

    sf::VertexArray bottom(sf::Lines, 2);
    bottom[0] = sf::Vertex(begin + sf::Vector2f(m_sit.getSize().x - 15.f , m_sit.getSize().y -45.f) , sf::Color::Black);
    bottom[1] = sf::Vertex(m_sit.getPosition(), sf::Color::Black);
    w.draw(bottom);
    sf::VertexArray top(sf::Lines, 2);
    top[0] = sf::Vertex(begin + sf::Vector2f(-50.f,0.f), sf::Color::Black);
    top[1] = sf::Vertex(m_sit.getPosition() , sf::Color::Black);
    w.draw(top);
  
}

//to "register" the object in the Factory
static auto registerItWood = ObjectFactory<StaticObjects>::instance().registerType(
    "rogatka",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr) -> std::unique_ptr<StaticObjects>
    {
        return std::make_unique<Rogatka>(world, position, size, arr);
    }
);