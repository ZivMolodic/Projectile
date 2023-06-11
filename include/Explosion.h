#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class Explosion {
public:
    Explosion(const sf::Vector2f& position, float radiusLimit) : m_radiusLimit(radiusLimit) {
        m_shape.setFillColor(sf::Color::Red);
        m_shape.setRadius(0);
        m_shape.setOrigin(0, 0);
        m_shape.setPosition(position);
    }

    void update() {
        if (auto radius = m_shape.getRadius(); radius < m_radiusLimit) {
            m_shape.setRadius(radius+25.f);
            m_shape.setOrigin(radius, radius);
        }
    }

    bool isFinished() const {
        return m_shape.getRadius() >= m_radiusLimit;
    }

    void draw(sf::RenderWindow* window) const {
        window->draw(m_shape);
    }

private:
    float m_radiusLimit;
    sf::CircleShape m_shape;
};
