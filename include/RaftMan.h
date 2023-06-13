#pragma once
//#include "GameObject.h"
#include <memory>
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Resources.h"
#include "PhysicsBehavior.h"

class Player;


class RaftMan
{
public:
	RaftMan(std::weak_ptr<Player> team, const sf::Vector2f& position);
	
	void draw(sf::RenderWindow* window) const;
	void useWeapon(std::weak_ptr<Weapon> weapon) { m_weapon = weapon; }
	void play(sf::RenderWindow* window, const sf::Event& event);
	void update() { m_physics.update(&m_body); }
	void handleCollision(const sf::RectangleShape& rec = sf::RectangleShape());
private:
	bool m_jumps;
	int m_life;
	sf::RectangleShape m_body;
	std::weak_ptr<Player> m_team;
	std::weak_ptr<Weapon> m_weapon;
	RectanglePhysics m_physics;
};

