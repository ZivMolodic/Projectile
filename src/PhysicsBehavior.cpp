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
    if (norma < 0.5)
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
    Vector2f fix = surface;

    auto res = m_velocity - 2 * dotProduct(m_velocity, fix) * fix;
    if (res.y > 0)
        res = res;
    /*if (m_velocity.x > 0)
        setVelocity((res - Vector2f{ 0.1f,0.f }) * BOUNCE_FACTOR);
    else
        setVelocity((res + Vector2f{ 0.1f,0.f }) * BOUNCE_FACTOR);*/
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
    if (auto intersection = circleIntersectionPoint(position, m_velocity, radius, rec); intersection != Vector2f{ -1.f,-1.f })
    {
        static int x = 0;
        x++;
        if (x == 3)
            x = 3;
        auto direction = m_velocity;
        auto s = hitDirection(direction, intersection);
        if (s != Vector2f{ -1,0 } && s != Vector2f{ 1,0 } && s != Vector2f{ 0,1 } && s != Vector2f{ 0,-1 })
            s = s;

        handleHit(s);
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


Vector2f PhisycsBehavior::circleIntersectionPoint(const sf::Vector2f& center, const sf::Vector2f& direction, float radius, const RectangleShape& rec)
{
    if (rec.getSize() == sf::Vector2f{ 0,0 })
        return Vector2f(-1.f, -1.f);

    if (center.y + radius - 10 > 400)
        int x = 0;

    float angleIncrement = 3.14159f / (2 * NUMOFPOINTS);  // Half of the circle

    sf::Vector2f normalizedDirection = direction / std::sqrt(direction.x * direction.x + direction.y * direction.y);
    float startingAngle = std::atan2(normalizedDirection.y, normalizedDirection.x);

    for (unsigned int i = 0; i < NUMOFPOINTS / 2; ++i)
    {
        float angle = startingAngle + i * angleIncrement;
        float x = radius * std::cos(angle);
        float y = radius * std::sin(angle);
        if (isPointInRotatedRectangle(center + sf::Vector2f(x, y), rec))
            return center + Vector2f(x, y);
        angle = startingAngle - i * angleIncrement;
        x = radius * std::cos(angle);
        y = radius * std::sin(angle);
        if (isPointInRotatedRectangle(center + sf::Vector2f(x, y), rec))
            return center + Vector2f(x, y);
    }

    return Vector2f(-1.f, -1.f);
}


bool PhisycsBehavior::isPointInRotatedRectangle(const sf::Vector2f& point, const sf::RectangleShape& rectangle)
{
    if (rectangle.getRotation() == 0)
        return rectangle.getGlobalBounds().contains(point);


    sf::Transform transform = rectangle.getTransform();
    sf::FloatRect localBounds = rectangle.getLocalBounds();

    sf::Vector2f vertices[4] = {
        transform.transformPoint(localBounds.left, localBounds.top),
        transform.transformPoint(localBounds.left + localBounds.width, localBounds.top),
        transform.transformPoint(localBounds.left + localBounds.width, localBounds.top + localBounds.height),
        transform.transformPoint(localBounds.left, localBounds.top + localBounds.height)
    };

    sf::Vector2f edgeNormals[4] = {
        sf::Vector2f(0.f, -1.f), // Top edge normal
        sf::Vector2f(1.f, 0.f),  // Right edge normal
        sf::Vector2f(0.f, 1.f),  // Bottom edge normal
        sf::Vector2f(-1.f, 0.f)  // Left edge normal
    };

    for (int i = 0; i < 4; ++i) {
        sf::Vector2f p1 = vertices[i];
        sf::Vector2f p2 = vertices[(i + 1) % 4];

        sf::Vector2f edge = p2 - p1;
        sf::Vector2f edgeNormal = edgeNormals[i];

        sf::Vector2f pointToVertex = point - p1;

        if (dotProduct(edgeNormal, edge) < 0.f) {
            edgeNormal = -edgeNormal;
        }

        if (dotProduct(edgeNormal, pointToVertex) < 0.f) {
            return false;
        }
    }

    return true;
}



sf::Vector2f PhisycsBehavior::getIntersectionPoint(const sf::RectangleShape& rect1, const sf::RectangleShape& rect2) {
    sf::Transform transform1 = rect1.getTransform();
    sf::Transform transform2 = rect2.getTransform();
    sf::FloatRect localBounds1 = rect1.getLocalBounds();
    sf::FloatRect localBounds2 = rect2.getLocalBounds();

    sf::Vector2f vertices1[4] = {
        transform1.transformPoint(localBounds1.left, localBounds1.top),
        transform1.transformPoint(localBounds1.left + localBounds1.width, localBounds1.top),
        transform1.transformPoint(localBounds1.left + localBounds1.width, localBounds1.top + localBounds1.height),
        transform1.transformPoint(localBounds1.left, localBounds1.top + localBounds1.height)
    };

    sf::Vector2f vertices2[4] = {
        transform2.transformPoint(localBounds2.left, localBounds2.top),
        transform2.transformPoint(localBounds2.left + localBounds2.width, localBounds2.top),
        transform2.transformPoint(localBounds2.left + localBounds2.width, localBounds2.top + localBounds2.height),
        transform2.transformPoint(localBounds2.left, localBounds2.top + localBounds2.height)
    };

    for (int i = 0; i < 4; ++i) {
        sf::Vector2f p1 = vertices1[i];
        sf::Vector2f p2 = vertices1[(i + 1) % 4];

        for (int j = 0; j < 4; ++j) {
            sf::Vector2f p3 = vertices2[j];
            sf::Vector2f p4 = vertices2[(j + 1) % 4];

            float denominator = (p1.x - p2.x) * (p3.y - p4.y) - (p1.y - p2.y) * (p3.x - p4.x);
            if (denominator != 0.f) {
                float t = ((p1.x - p3.x) * (p3.y - p4.y) - (p1.y - p3.y) * (p3.x - p4.x)) / denominator;
                float u = -((p1.x - p2.x) * (p1.y - p3.y) - (p1.y - p2.y) * (p1.x - p3.x)) / denominator;

                if (t >= 0.f && t <= 1.f && u >= 0.f && u <= 1.f) {
                    float intersectionX = p1.x + t * (p2.x - p1.x);
                    float intersectionY = p1.y + t * (p2.y - p1.y);
                    return sf::Vector2f(intersectionX, intersectionY);
                }
            }
        }
    }

    // No intersection
    return sf::Vector2f(-1.f, -1.f);
}



Vector2f PhisycsBehavior::hitDirection(const sf::Vector2f& direction, const sf::Vector2f& intersectionPoint)
{
    float angle = std::atan2(direction.y, direction.x);
    float x = intersectionPoint.x;
    float y = intersectionPoint.y;

    float angleThreshold = 3.14159f / 4.0f;  // 45 degrees threshold

    // Calculate the absolute angle difference between the hit direction and each side
    float topAngleDiff = std::abs(angle - (-3.14159f / 2.0f));
    float bottomAngleDiff = std::abs(angle - (3.14159f / 2.0f));
    float leftAngleDiff = std::abs(angle - 3.14159f);
    float rightAngleDiff = std::abs(angle);

    if (topAngleDiff <= angleThreshold && y < 0.0f)
        return { 0,1 };
    else if (bottomAngleDiff <= angleThreshold && y > 0.0f)
        return { 0,-1 };
    else if (leftAngleDiff <= angleThreshold && x < 0.0f)
        return { 1,0 };
    else if (rightAngleDiff <= angleThreshold && x > 0.0f)
        return { -1,0 };
    else
        return { 1,1 };
}