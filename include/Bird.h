#pragma once

#include "Objects.h"



class Bird: public Objects
{
    //public Objects
public:

	Bird(std::shared_ptr<World> world,const sf::Vector2f &position, const sf::Vector2f& size, const int& index);
    virtual ~Bird() = default;
    
    //virtual funcs
    virtual void objectUpdate();
    virtual void drawObject(sf::RenderWindow& window);
    virtual void handleEvent(sf::Event& event, const sf::Vector2f& mouse);
    virtual sf::Vector2f getPosition() const override;

    //setters and methods
    void applyForce(const sf::Vector2f& force);
    void handleThrow(const float x, const float y);
    void setRangeVector(const sf::Vector2i& mouseLocation, sf::RenderWindow& w);
    void setPosition(const sf::Vector2f& pos);
    inline void setOnRogatka(const bool& is) { m_onRogatka = is; m_body->SetEnabled(true); };
    inline void gotHit() { m_hit = true; };

    //getters
    sf::Vector2f calculateThrow() const;
    inline bool isDragged() const { return m_dragging; };
    inline sf::Vector2f getBeginPosition() const { return dragStartPosition; };
    inline bool isOnRogatka() const { return m_onRogatka; };
    inline float getBirdAngle() const { return m_bird.getRotation(); };
    inline bool isHit() const { return m_hit; };

    


protected:
    sf::CircleShape m_bird;
    virtual void rotate(const int& x) {};

private:

    int m_BirdType;

    bool m_onRogatka;
    bool m_dragging;
    bool m_hit;

    //dragging positions
    sf::Vector2f dragStartPosition;
    sf::Vector2f dragEndPosition;
     
    //private functions
    void initPhysicBody(std::shared_ptr<World> world, const sf::Vector2f& position, const sf::Vector2f& size)override;
    void initGraphicBody(const sf::Vector2f& size = {20.f, 0.f}) override;
};


