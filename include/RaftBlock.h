#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameObject.h"

class RaftBlock: public GameObject
{
public:
	RaftBlock(const sf::Vector2f& position)
		: GameObject({160,70}, position,'#'), m_durability(150)
	{}
	void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override 
	{ 
		window->draw(*m_shape);
		auto rec = this->getRectangle();
		rec.setFillColor(sf::Color::Blue);
		window->draw(rec);
	}
	void update() override {}
	sf::RectangleShape getRectangle() const
	{
		auto rec = sf::RectangleShape({ 160, 20 });
		rec.setPosition(getPosition().x - 80, getPosition().y - 10);
		return rec; 
	}

private:
	int m_durability;
};
