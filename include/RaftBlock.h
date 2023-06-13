#pragma once
#include <SFML/Graphics.hpp>
#include "Resources.h"
#include "GameObject.h"

class RaftBlock: public GameObject
{
public:
	RaftBlock(const sf::Vector2f& position)
		: GameObject({160,70}, position,'#'), m_durability(150)
	{
		//m_formation.setPosition(position);
		//m_formation.setOutlineThickness(3.f);
		//m_formation.setOutlineColor(sf::Color::Green);
		//m_formation.setTexture(&Resources::instance().getTexture('#'), true);
		//auto rec = m_formation.getTextureRect();
		//rec = rec;
		//auto d = sf::IntRect()
		//sf::IntRect textureRect(0.f, -400,1280, 100);
		//m_formation.setTextureRect(textureRect);
	}
	void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override { window->draw(*m_shape); }
	sf::RectangleShape getRec()
	{
		auto rec = sf::RectangleShape({ 100, 15 });
		rec.setPosition(getPosition().x - 50, getPosition().y);
		return rec; 
	}

private:
	//sf::Vector2f m_position; //?
	int m_durability;
	//sf::RectangleShape m_formation;
};
