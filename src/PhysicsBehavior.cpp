#include "PhysicsBehavior.h"

void PhisycsBehavior::setVelocity(const Vector2f& velocity) 
{
    auto norma = std::sqrtf(norm(velocity));
    if (norma > 40.f)
        m_velocity = (velocity / norma) * 40.f;
    else
        m_velocity = velocity;
}


void PhisycsBehavior::update(Transformable* body) {
    auto norma = std::sqrtf(norm(m_velocity));
    if (norma < 0.01f)
        m_velocity = sf::Vector2f(0, 0);
    else
    {
        m_velocity.y += GRAVITY * m_weight;
        auto angle = std::atan2(m_velocity.y, m_velocity.x);
        auto rotation = angle * 180.f / 3.14f;
        body->setRotation(rotation + 90);
        //body->velocity.x *= 0.9f;
        body->move(m_velocity * (m_timer.restart().asMilliseconds() * 0.08f));
        //body->move(m_velocity * (0.08f));
    }
}


void PhisycsBehavior::handleHit(const Vector2f& surface) {
    
    Vector2f fix = surface / std::sqrtf(norm(surface));
    auto res = m_velocity - 2 * dotProduct(m_velocity, fix) * fix;
    
    setVelocity(res * BOUNCE_FACTOR);
}


sf::Vector2f PhisycsBehavior::manageCollision(const sf::Vector2f& position, float radius, const RectangleShape& rec)
{
    if (position.y + radius >= BACKGROUND_SIZE.y)
    {
        handleHit({ 0,1 });
        return sf::Vector2f(position.x, BACKGROUND_SIZE.y - (radius + 1));
    }
    if (position.x + radius >= BACKGROUND_SIZE.x)
    {
        //bird.velocity.x *= -BOUNCE_FACTOR;
        handleHit({ 1,0 });
        return sf::Vector2f(BACKGROUND_SIZE.x - (radius + 1), position.y);
    }
    if (position.x <= 0)
    {
        //bird.velocity.x *= -BOUNCE_FACTOR;
        handleHit({ 1,0 });
        return sf::Vector2f(1 + radius, position.y);
    }
    if (auto response = responseVector(position, m_velocity, radius, rec); response != Vector2f{ 0,0 })
    {
        auto direction = m_velocity;

        handleHit(response);

        auto pos = position;

        auto normDirection = Vector2f{ direction.x / std::sqrtf(norm(direction)), direction.y / std::sqrtf(norm(direction)) };
        while (isPointInRotatedRectangle(pos + normDirection * (radius + 0.2f), rec))
            pos -= normDirection * 0.1f;
        //pos -= normDirection * 3.f;
        return(pos);
        //bird.shape.setPosition(Vector2f{bird.shape.getPosition().x, 462.5f - bird.shape.getRadius()});
        //bird.shape.setPosition(intersection - normDirection * bird.shape.getRadius());
    }
    return sf::Vector2f(0, 0);
}

Vector2f PhisycsBehavior::responseVector(const sf::Vector2f& center, const sf::Vector2f& direction, float radius, const RectangleShape& rec)
{
    int count = 0;
    sf::Vector2f response;
    float angleIncrement = 3.14159f / (2 * NUMOFPOINTS);  // Half of the circle

    sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float startingAngle = std::atan2(normalizedDirection.y, normalizedDirection.x);

    for (unsigned int i = 0; i < NUMOFPOINTS / 2; ++i)
    {
        float angle = startingAngle + i * angleIncrement;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        if (isPointInRotatedRectangle(center + sf::Vector2f(x, y), rec))
        {
            response -= Vector2f(x, y);
            count++;
        }
        angle = startingAngle - i * angleIncrement;
        x = radius * std::cos(angle);
        y = radius * std::sin(angle);
        if (isPointInRotatedRectangle(center + sf::Vector2f(x, y), rec))
        {
            response -= Vector2f(x, y);
            count++;
        }
    }

    //if (count > 10)
        return response;

    return { 0,0 };
}

bool PhisycsBehavior::isPointInRotatedRectangle(const sf::Vector2f& point, const sf::RectangleShape& rectangle)
{
    if (rectangle.getRotation() == 0)
        return rectangle.getGlobalBounds().contains(point);
 
    sf::FloatRect bounds = rectangle.getGlobalBounds();
    sf::Vector2f center = rectangle.getPosition();
    sf::Vector2f halfSize = rectangle.getSize() * 0.5f;
    float rotation = rectangle.getRotation();

    // Convert the point to local coordinates
    sf::Vector2f localPoint = point - center;
    float angleRad = rotation * 3.14159f / 180.0f;
    float sinRotation = std::sin(angleRad);
    float cosRotation = std::cos(angleRad);
    localPoint = sf::Vector2f(localPoint.x * cosRotation + localPoint.y * sinRotation,
        -localPoint.x * sinRotation + localPoint.y * cosRotation);
    // Check if the point is within the transformed rectangle
    return (localPoint.x >= -halfSize.x && localPoint.x <= halfSize.x &&
        localPoint.y >= -halfSize.y && localPoint.y <= halfSize.y);
}


