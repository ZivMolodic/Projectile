#pragma once
//#include "GameObject.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Resources.h"
#include "PhysicsBehavior.h"
#include "GameObject.h"

class Player;


class RaftMan: public DynamicObject
{
public:
	RaftMan(std::weak_ptr<Player> team, const sf::Vector2f& position);
	
	void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override;
	void useWeapon(std::weak_ptr<Weapon> weapon) { m_weapon = weapon; }
	void play(sf::RenderWindow* window, const sf::Event& event);
	void update() override;
	void handleCollision(const sf::RectangleShape& rec = sf::RectangleShape()) override;
private:
	bool m_jumps;
	int m_life;
	//sf::RectangleShape m_body;
	std::weak_ptr<Player> m_team;
	std::weak_ptr<Weapon> m_weapon;
	//RectanglePhysics m_physics;
};

