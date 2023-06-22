#pragma once
#include "GameObject.h"
//#include "Player.h"
#include <SFML/Graphics.hpp>

class Player;
class RaftBlock;

class Board
{
public:
	Board(const sf::Vector2f& playerPosition, const sf::Vector2f& computerPosition, int numOfRaftMen);
	void addObject(GameObject* object);
	void update() { for(auto& object: m_objects) object->update(); }
	void draw(RenderWindow* window);
	void play(RenderWindow* window, const sf::Event& event);
	void handleCollisions();
	sf::Vector2f getPlayerPosition() { return m_user->getPlayerPosition(); }

private:
	std::shared_ptr<Player> m_user;
	std::shared_ptr<Player> m_computer;
	std::vector<GameObject*> m_objects;
};