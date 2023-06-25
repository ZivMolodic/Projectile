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
	void raftManMove(sf::RenderWindow* window, const sf::Event& event);
	void playWithRaft(const enum Menu& button, sf::RenderWindow* window, const sf::Event& event);
	void playWithWeapon(const enum Menu& button, sf::RenderWindow* window, const sf::Event& event);
	void update() override;
	void handleCollision(const sf::RectangleShape& rec = sf::RectangleShape()) override;
	RaftBlock getRaftBlock() const { return *m_raftBlock; }

private:
	bool m_holdRaft;
	bool m_jumps;
	int m_life;
	enum Menu m_lastButton;
	std::weak_ptr<Player> m_team;
	std::weak_ptr<Weapon> m_weapon;
	std::unique_ptr<RaftBlock> m_raftBlock;
};

