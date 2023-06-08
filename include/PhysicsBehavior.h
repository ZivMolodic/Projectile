#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"

using namespace sf;


class PhisycsBehavior
{
public:
    PhisycsBehavior(float weight) : m_weight(weight), m_velocity{ 0,0 } { if (weight < 0)m_weight = 0; m_timer.restart(); }
    Vector2f getVelocity() const { return m_velocity; }
    void setVelocity(const Vector2f& velocity);
    void update(Transformable* body);
    void handleHit(const Vector2f& surface);
    sf::Vector2f manageCollision(const sf::Vector2f& position, float radius, const RectangleShape& rec = RectangleShape());
    Vector2f circleIntersectionPoint(const sf::Vector2f& center, const sf::Vector2f& direction, float radius, const RectangleShape& rec);
    bool isPointInRotatedRectangle(const sf::Vector2f& point, const sf::RectangleShape& rectangle);
    
    sf::Vector2f getIntersectionPoint(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2);
    Vector2f hitDirection(const sf::Vector2f& direction, const sf::Vector2f& intersectionPoint);
    
private:
    float dotProduct(const Vector2f& lhs, const Vector2f& rhs)
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y);
    }
    float norm(const Vector2f& vector)
    {
        return (vector.x * vector.x + vector.y * vector.y);
    }



    int m_weight;
    Vector2f m_velocity;
    Clock m_timer;
};
