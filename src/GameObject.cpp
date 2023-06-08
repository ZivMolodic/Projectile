#include "GameObject.h"
#include "Resources.h"
#include <iostream>

using namespace sf;

GameObject::GameObject(Vector2f size, sf::Vector2f position, char c)
{
	m_texture.setSize(size);
	m_texture.setPosition(position);
	m_texture.setTexture(&Resources::instance().getTexture(c));
}