#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsBehavior.h"
#include "Resources.h"
#include "Explosion.h"


class Objectile
{
public:
    Objectile(const sf::Vector2f& position, const sf::Vector2f& destination) : m_physics( 20.f, 0.5f , 1 ), m_setteled(false), m_explosion(nullptr) {
        m_physics.setBodyToRotate(true);
        m_shape.setRadius(20.f);
        m_shape.setOrigin({ m_shape.getRadius(), m_shape.getRadius() });
        m_shape.setPosition({ position.x + m_shape.getRadius(), position.y + m_shape.getRadius() });
        m_shape.setTexture(&Resources::instance().getTexture('*'));
        launch(destination);
        m_timer.restart();
    }
    void handleCollision(const RectangleShape& rec) {
        if (auto update = m_physics.manageCollision(m_shape.getPosition(), rec); update != sf::Vector2f(0, 0))
            m_shape.setPosition(update);

        if (m_physics.getVelocity() == sf::Vector2f(0, 0))
            m_setteled = true;
    }
    
    void update() 
    {
        if (m_explosion)
            m_explosion->update();
        
        else if (m_timer.getElapsedTime().asSeconds() > 3)
            m_explosion = std::make_unique<Explosion>(m_shape.getPosition(), 150.f);

        else
        {
            m_physics.update(&m_shape);

            if (m_physics.getVelocity() == sf::Vector2f(0, 0))
                m_setteled = true;
        }

        
        //if (auto update = m_physics.manageCollision(m_shape.getPosition(), m_shape.getRadius()); update != sf::Vector2f(0, 0))
        //    m_shape.setPosition(update);

        //if (m_physics.getVelocity() == sf::Vector2f(0,0))
        //    m_setteled = true;
    }
    void draw(RenderWindow* window) { if (!m_explosion) window->draw(m_shape); else m_explosion->draw(window); }
    sf::Vector2f getPosition() { return m_shape.getPosition(); }
    bool setteled() { if (m_explosion) return m_explosion->isFinished(); return false; }

private:
    void launch(const Vector2f& velocity) { m_physics.setVelocity(velocity); }
    sf::CircleShape m_shape;
    CirclePhysics m_physics;
    bool m_setteled;
    sf::Clock m_timer;
    std::unique_ptr<Explosion> m_explosion;
};
