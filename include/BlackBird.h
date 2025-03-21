#pragma once
#include "Bird.h"

class BlackBird : public Bird
{
public:
    BlackBird(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size, const arrData &arr = {3,BIRD_HP,0});
    virtual ~BlackBird();

    //virtual funcs
    virtual void handleEvent(sf::Event& event, const sf::Vector2f& mouse)override;
    virtual void drawObject(sf::RenderWindow& w)override;

private:
    bool m_activated;
    bool m_exploded;

    std::shared_ptr<World> m_world;
    std::vector<b2Body*> m_bombs;
    sf::Clock m_clock;

    //private funcs
    void explode();
    void setBombs();
    void PhysicBombBody(const int &index, const sf::Vector2f& position);
    void destroyedBody();
};
