#include "BlueBird.h"


BlueBird::BlueBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr)
    : Bird(world, position, size, arr.at(0)), m_world{ world}, isSplit{false}, m_state{normal} {
	 
}


void BlueBird::objectUpdate() {
    
   
    if (m_state == normal) {
        b2Vec2 position = m_body->GetPosition();
        float angle = m_body->GetAngle();
        m_bird.setPosition(position.x * SCALE, position.y * SCALE);
        m_bird.setRotation(angle * 180.0f / b2_pi);
    }
    else if (m_state == split) {
        for (auto& ea : m_split)
            ea->objectUpdate();
    }

}


void BlueBird::drawObject(sf::RenderWindow& w) {
    
    if (m_state == normal)
    {
        this->objectUpdate();
        w.draw(m_bird);
    }
     
    else if (m_state == split) {
        for (auto& ea : m_split) {
            ea->objectUpdate();
            ea->drawObject(w);
        }
        Bird::objectUpdate();
        Bird::drawObject(w);
    }
}

void BlueBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse) {

    switch (event.type) {

    case sf::Event::MouseButtonPressed:

        if (!isHit() && event.mouseButton.button == sf::Mouse::Left && isSplit) {

            b2Vec2 force{ m_body->GetLinearVelocity() };
            force *= 4.f;
            sf::Vector2f location = this->getPosition();
            this->setBodySize();

            m_split[0] = std::make_unique<BlueBird>(m_world, sf::Vector2f(location.x, location.y - BLUE_BIRDS_DISTANCE), sf::Vector2f(15.f, 0.f));
            m_split[1] = std::make_unique<BlueBird>(m_world, sf::Vector2f(location.x, location.y + BLUE_BIRDS_DISTANCE), sf::Vector2f(15.f, 0.f));
            for (auto& ea : m_split) {
                ea->setEnable();
                ea->applyForce(sf::Vector2f(force.x, force.y));
            }
            this->applyForce(sf::Vector2f(force.x, force.y));
           
            isSplit = false;
            m_state = split;
           
        }

        if (event.mouseButton.button == sf::Mouse::Left) {
            this->handleThrow(mouse.x, mouse.y);
        }

        break;
    case sf::Event::MouseButtonReleased:
       
        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
            sf::Vector2f force = this->calculateThrow();
            this->applyForce(force);
            isSplit = true;
        }
        break;


    }

}

void BlueBird::setBodySize() {
    b2CircleShape* circleShape = static_cast<b2CircleShape*>(m_body->GetFixtureList()->GetShape());
    circleShape->m_radius = BLUE_BIRD_SPLIT_RADIUS / SCALE;
    m_bird.setRadius(BLUE_BIRD_SPLIT_RADIUS);
    m_body->ResetMassData();
}

static auto registerItYBlueBird = ObjectFactory<Bird>::instance().registerType(
    "BlueBird",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr) -> std::unique_ptr<Bird>
    {
        return std::make_unique<BlueBird>(world, position, size, arr);
    }
);

