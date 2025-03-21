
#include "YellowBird.h"

YellowBird::YellowBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, const arrData& arr)
    : Bird(world, position, size, arr.at(0)), m_secondclick{ false } {
    
}



void YellowBird::handleEvent(sf::Event& event, const sf::Vector2f& mouse)
{
    switch (event.type) {
       
    case sf::Event::MouseButtonPressed:

        if (!isHit() && event.mouseButton.button == sf::Mouse::Left && m_secondclick && !isDragged()) {
          
            b2Vec2 force{m_body->GetLinearVelocity()};
            force.Normalize();
            force *= 3.f;
            this->applyForce(sf::Vector2f(force.x * SCALE , force.y * SCALE));
            m_secondclick = false;
        }
        if (event.mouseButton.button == sf::Mouse::Left) {
            this->handleThrow(mouse.x, mouse.y);
        }
        
        break;
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left && isDragged()) {
            sf::Vector2f force = this->calculateThrow();
            this->applyForce(force);
            m_secondclick = true;
        }

        break;


    }
}


//to "register" the object in the Factory
static auto registerItYellowBird = ObjectFactory<Bird>::instance().registerType(
    "YellowBird",
    [](std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, arrData arr) -> std::unique_ptr<Bird>
    {
        return std::make_unique<YellowBird>(world, position, size, arr);
    }
);
