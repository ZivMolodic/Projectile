#pragma once
//#include "Macros.h"
#include <SFML/Graphics.hpp>
#include <memory>
#include "PhysicsBehavior.h"

using namespace sf;

class GameObject
{
public:
	//GameObject() {};
	GameObject(const sf::Vector2f& size, const sf::Vector2f& position, char c);
	GameObject(float radius, const sf::Vector2f& position, char c);
	~GameObject(){}
	sf::FloatRect getGlobalBounds() { return m_shape->getGlobalBounds(); }
	sf::Vector2f getPosition() const { return m_shape->getPosition(); }
	void setPosition(const sf::Vector2f& position) { m_shape->setPosition(position); }
	//virtual void update() = 0;
	virtual void draw(RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const = 0;

protected:
	std::shared_ptr<sf::Shape> m_shape;
};


class DynamicObject : public GameObject
{
public:
	DynamicObject(const sf::Vector2f& size, const sf::Vector2f& position, char c, float bounce, float weight);
	DynamicObject(float radius, const sf::Vector2f& position, char c, float bounce, float weight);
	virtual void update() = 0;
	virtual void handleCollision(const sf::RectangleShape& rec = sf::RectangleShape()) = 0;

protected:
	std::shared_ptr<PhysicsBehavior> m_physics;
};
