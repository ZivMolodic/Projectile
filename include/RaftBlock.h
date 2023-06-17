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
	}
	sf::RectangleShape getRec() const
	{
		auto rec = sf::RectangleShape({ 100, 15 });
		rec.setPosition(getPosition().x - 50, getPosition().y - 10);
		rec.setFillColor(sf::Color::Magenta);
		return rec; 
	}

private:
	int m_durability;
};
