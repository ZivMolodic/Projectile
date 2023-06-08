#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsBehavior.h"
#include "Resources.h"


class Objectile
{
public:
    Objectile(const sf::Vector2f& position, const sf::Vector2f& destination) : m_physics{ 1 }, m_setteled(false) {
        m_shape.setRadius(20.f);
        m_shape.setOrigin({ m_shape.getRadius(), m_shape.getRadius() });
        m_shape.setPosition({ position.x + m_shape.getRadius(), position.y + m_shape.getRadius() });
        //m_shape.setFillColor(sf::Color::Cyan);
        m_shape.setTexture(&Resources::instance().getTexture('*'));
        launch(destination);
    }
    void handleCollision(const RectangleShape& rec) {
        if (auto update = m_physics.manageCollision(m_shape.getPosition(), m_shape.getRadius(), rec); update != sf::Vector2f(0, 0))
            m_shape.setPosition(update);

        if (m_physics.getVelocity() == sf::Vector2f(0, 0))
            m_setteled = true;
    }
    
    void update() 
    {
        m_physics.update(&m_shape);
        if (m_physics.getVelocity() == sf::Vector2f(0, 0))
            m_setteled = true;
        //if (auto update = m_physics.manageCollision(m_shape.getPosition(), m_shape.getRadius()); update != sf::Vector2f(0, 0))
        //    m_shape.setPosition(update);

        //if (m_physics.getVelocity() == sf::Vector2f(0,0))
        //    m_setteled = true;
    }
    void draw(RenderWindow* window) { window->draw(m_shape); }
    sf::Vector2f getPosition() { return m_shape.getPosition(); }
    bool setteled() { return m_setteled; }

private:
    void launch(const Vector2f& velocity) { m_physics.setVelocity(velocity); }
    sf::CircleShape m_shape;
    PhisycsBehavior m_physics;
    bool m_setteled;
};
