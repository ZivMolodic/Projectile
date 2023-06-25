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
	RaftMan(Player* team, const sf::Vector2f& position);
	void shoot(const sf::Vector2f& velocity);
	void draw(sf::RenderWindow* window, const sf::Vector2f& position = sf::Vector2f()) const override;
	void useWeapon(std::weak_ptr<Weapon> weapon) { m_weapon = weapon; }
	void play(sf::RenderWindow* window, const sf::Event& event, const Direction& direction = Direction::NA);
	void update() override;
	void handleExplosion(const Explosion& explosion);
	void handleCollision(const sf::RectangleShape& rec = sf::RectangleShape()) override;
private:
	bool m_jumps;
	int m_life;
	Player* m_team;
	std::weak_ptr<Weapon> m_weapon;
};

