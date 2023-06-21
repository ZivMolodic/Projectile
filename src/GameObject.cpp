#include "GameObject.h"
#include "Resources.h"
#include <iostream>

using namespace sf;

GameObject::GameObject(const sf::Vector2f& size, const sf::Vector2f& position, char c)
	: m_dead(false)
{
	m_shape = std::make_shared<sf::RectangleShape>(size);
	m_shape->setOrigin(size / 2.f);
	m_shape->setPosition(position);
	m_shape->setTexture(&Resources::instance().getTexture(c));
}
GameObject::GameObject(float radius, const sf::Vector2f& position, char c)
{
	m_shape = std::make_shared<sf::CircleShape>(radius);
	m_shape->setOrigin({radius, radius});
	m_shape->setPosition(position);
	m_shape->setTexture(&Resources::instance().getTexture(c));
}


DynamicObject::DynamicObject(const sf::Vector2f& size, const sf::Vector2f& position, char c, float bounce, float weight)
	: GameObject(size, position, c)
{
	m_physics = std::make_shared<RectanglePhysics>(size, bounce, weight);
}

DynamicObject::DynamicObject(float radius, const sf::Vector2f& position, char c, float bounce, float weight)
	: GameObject(radius, position, c)
{
	m_physics = std::make_shared<CirclePhysics>(radius, bounce, weight);
}
