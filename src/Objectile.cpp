#include "Objectile.h"


Objectile::Objectile(const sf::Vector2f& position, const sf::Vector2f& destination)
    : DynamicObject(20,position,'*',0.3f,1), m_setteled(false), m_explosion(nullptr)
{
    //m_physics.setBodyToRotate(true);
    //m_shape.setRadius(20.f);
    //m_shape.setOrigin({ m_shape.getRadius(), m_shape.getRadius() });
    //m_shape.setPosition({ position.x + m_shape.getRadius(), position.y + m_shape.getRadius() });
    //m_shape.setTexture(&Resources::instance().getTexture('*'));
    m_physics->setBodyToRotate(true);
    launch(destination);
    m_timer.restart();
}

void Objectile::handleCollision(const RectangleShape& rec) {
    if (auto update = m_physics->manageCollision(getPosition(), rec); update != sf::Vector2f(0, 0))
        m_shape->setPosition(update);

    if (m_physics->getVelocity() == sf::Vector2f(0, 0))
        m_setteled = true;
}

void Objectile::update()
{
    if (m_explosion)
        m_explosion->update();

    else if (m_timer.getElapsedTime().asSeconds() > 3)
        m_explosion = std::make_shared<Explosion>(getPosition(), 150.f);

    else
    {
        m_physics->update(m_shape);

        if (m_physics->getVelocity() == sf::Vector2f(0, 0))
            m_setteled = true;
    }


    //if (auto update = m_physics.manageCollision(m_shape.getPosition(), m_shape.getRadius()); update != sf::Vector2f(0, 0))
    //    m_shape.setPosition(update);

    //if (m_physics.getVelocity() == sf::Vector2f(0,0))
    //    m_setteled = true;
}