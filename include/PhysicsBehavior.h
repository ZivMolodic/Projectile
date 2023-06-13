#pragma once
#include <SFML/Graphics.hpp>
#include "Macros.h"
#include <set>

using namespace sf;


class PhisycsBehavior
{
public:
    PhisycsBehavior(float bounce, float weight) : m_weight(weight), m_velocity{ 0,0 } , m_rotate(false), m_bounce(bounce) { if (weight < 0)m_weight = 1; m_timer.restart(); }
    Vector2f getVelocity() const { return m_velocity; }
    void setVelocity(const Vector2f& velocity);
    void setBodyToRotate(bool rotate = true) { m_rotate = rotate; }
    void setBounce(float bounce) { (bounce >= 0) ? m_bounce = bounce : m_bounce = 0; }
    float getBounce() { return m_bounce; }
    void update(Transformable* body);
    virtual sf::Vector2f manageCollision(const sf::Vector2f& position, const RectangleShape& rec = RectangleShape()) = 0;
    
protected:
    void handleHit(const Vector2f& surface);
    float dotProduct(const Vector2f& lhs, const Vector2f& rhs)
    {
        return (lhs.x * rhs.x + lhs.y * rhs.y);
    }
    float norm(const Vector2f& vector)
    {
        return (vector.x * vector.x + vector.y * vector.y);
    }

private:
    float m_bounce;
    bool m_rotate;
    int m_weight;
    Vector2f m_velocity;
    Clock m_timer;
};


class CirclePhysics : public PhisycsBehavior
{
public:
    CirclePhysics(float radius, float bounce, float weight) : PhisycsBehavior(bounce, weight), m_radius(radius){}
    virtual sf::Vector2f manageCollision(const sf::Vector2f& position, const RectangleShape& rec = RectangleShape()) override;

private:
    bool isPointInRotatedRectangle(const sf::Vector2f& point, const sf::RectangleShape& rectangle);
    Vector2f responseVector(const sf::Vector2f& center, const sf::Vector2f& direction, float radius, const RectangleShape& rec);

    float m_radius;
};

class RectanglePhysics : public PhisycsBehavior
{
public:
    RectanglePhysics(const sf::Vector2f& size, float bounce, float weight): PhisycsBehavior(bounce, weight), m_size(size) {}
    virtual sf::Vector2f manageCollision(const sf::Vector2f& position, const RectangleShape& rec = RectangleShape()) override;
    
private:
    sf::Vector2f AABBResponse(const sf::RectangleShape& rec1, const sf::RectangleShape& rec2);

    sf::Vector2f m_size;
};