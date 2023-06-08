#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Objectile.h"
#include "Resources.h"

class Weapon
{
public:
	Weapon()
		: m_objectile(nullptr), m_ammo(3), m_body(sf::Vector2f(55.f, 25.f))
	{
		m_body.setOrigin({ 0 , m_body.getSize().y / 2.f});
		m_body.setTexture(&Resources::instance().getTexture('g'));
	}
	bool firing() const { return m_objectile != nullptr; }
	void shot(const sf::Vector2f& destination) 
	{	
		auto rec = m_body;
		rec.setOrigin(0, 0);
		sf::FloatRect localBounds = rec.getLocalBounds();
		auto topRight = sf::Vector2f(localBounds.left + localBounds.width, localBounds.top);
		auto pos = rec.getTransform().transformPoint(topRight);

		//auto rec = m_body.getLocalBounds();
		//auto pos = sf::Vector2f(std::abs(rec.left - rec.width) / 2.f, std::abs(rec.top - rec.height) / 2.f);
		m_objectile = std::make_unique<Objectile>(pos, destination); 
	}
	void update() {
		if (m_objectile) { m_objectile->update(); if (m_objectile->setteled()) m_objectile.release(); }
	}
	void draw(RenderWindow* window, const sf::Vector2f& position) 
	{
		sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(*window));
		sf::Vector2f direction = mousePosition - position;
		float angle = std::atan2(direction.y, direction.x) * (180 / 3.14f);

		m_body.setPosition(position);
		m_body.setRotation(angle);
		window->draw(m_body);

		if (m_objectile)
			m_objectile->draw(window);
	}
	sf::Vector2f getObjectilePosition() { if (m_objectile) return m_objectile->getPosition(); }
	void handleCollision(const RectangleShape& rec) { if (m_objectile) m_objectile->handleCollision(rec); }

private:
	sf::RectangleShape m_body;
	std::unique_ptr<Objectile> m_objectile;
	int m_ammo;
};
