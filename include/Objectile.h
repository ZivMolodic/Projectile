#pragma once
#include "SFML/Graphics.hpp"
#include "PhysicsBehavior.h"
#include "Resources.h"
#include "Explosion.h"
#include "GameObject.h"


class Objectile: public DynamicObject
{
public:
    Objectile(const sf::Vector2f& position, const sf::Vector2f& destination);
    void handleCollision(const RectangleShape& rec) override;
    void update() override;
    void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override { if (!m_explosion) window->draw(*m_shape); else m_explosion->draw(window); }
    //sf::Vector2f getPosition() { return m_shape.getPosition(); }
    bool setteled() { if (m_explosion) return m_explosion->isFinished(); return false; }

private:
    void launch(const Vector2f& velocity) { m_physics->setVelocity(velocity); }
    //sf::CircleShape m_shape;
    //CirclePhysics m_physics;
    bool m_setteled;
    sf::Clock m_timer;
    std::shared_ptr<Explosion> m_explosion;
};
