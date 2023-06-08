#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"

//#include "GameObject.h"

class RaftBlock
{
public:
	RaftBlock(const sf::Vector2f& position)
		: m_formation({ 160,70 }), m_durability(75)
	{
		m_formation.setPosition(position);
		//m_formation.setOutlineThickness(3.f);
		//m_formation.setOutlineColor(sf::Color::Green);
		m_formation.setTexture(&Resources::instance().getTexture('#'), true);
		auto rec = m_formation.getTextureRect();
		rec = rec;
		//auto d = sf::IntRect()
		//sf::IntRect textureRect(0.f, -400,1280, 100);
		//m_formation.setTextureRect(textureRect);
	}
	void draw(sf::RenderWindow* window) { window->draw(m_formation); }
	sf::RectangleShape getRec() { return m_formation; }

private:
	//sf::Vector2f m_position; //?
	int m_durability;
	sf::RectangleShape m_formation;
};
