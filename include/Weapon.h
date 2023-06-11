#pragma once

#include <memory>
#include "SFML/Graphics.hpp"
#include "Objectile.h"
#include "Resources.h"
#include "RaftBlock.h"

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
		else
		{
			auto velocity = (mousePosition - m_body.getPosition());

			float initialSpeed = 100.f;
			float timeStep = 0.1f; // Adjust this value to control the smoothness of the trajectory
			float time = 0.f;
			float velocityX = abs(velocity.x) * cosf(angle * 3.14159f / 180.f);
			float velocityY = abs(velocity.y) * sin(angle * 3.14159f / 180.f);

			//auto velocity = sf::Vector2f(mousePosition.x, mousePosition.y) - m_body.getPosition();
			std::vector<sf::CircleShape> dots;
			auto potentialPosition = position;
			auto circle = sf::CircleShape(3);
			circle.setFillColor(sf::Color::Green);
			circle.setPosition(potentialPosition);
			dots.push_back(circle);

			for (int i = 0; i < 20; ++i)
			{
				time += timeStep;
				potentialPosition.x = position.x + velocityX * time ;
				potentialPosition.y = position.y + velocityY * time + 25.f * GRAVITY * time * time;

				auto c = sf::CircleShape(3);
				c.setFillColor(sf::Color::Green);
				c.setPosition(potentialPosition);
				dots.push_back(c);
			}
			
			for(const auto& dot: dots)
				window->draw(dot);
			auto rec = RaftBlock(sf::Vector2f(BACKGROUND_SIZE.x - 163, 400));
			//while (potentialPosition.y < BACKGROUND_SIZE.y && potentialPosition.x < BACKGROUND_SIZE.x)
			for(int i=0; i < 1000; ++i)
			{
				time += 1;
				if (rec.getRec().getGlobalBounds().contains(sf::Vector2f(position.x + velocityX * time, position.y + velocityY * time + 25.f * GRAVITY * time * time)))
					shot(velocity * 0.06f);
			}
		}
	}
	sf::Vector2f getObjectilePosition() { if (m_objectile) return m_objectile->getPosition(); }
	void handleCollision(const RectangleShape& rec) { if (m_objectile) m_objectile->handleCollision(rec); }

private:
	sf::RectangleShape m_body;
	std::unique_ptr<Objectile> m_objectile;
	int m_ammo;
};
