#pragma once
// #include "Macros.h"
#include <SFML/Graphics.hpp>

using namespace sf;

class GameObject
{
public:
	GameObject() {};
	GameObject(Vector2f size, sf::Vector2f position, char c);
	~GameObject(){}
	virtual void draw(RenderWindow* window) = 0;

protected:
	sf::RectangleShape m_texture;
};
