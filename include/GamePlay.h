#pragma once
#include <SFML\Graphics.hpp>
#include "Player.h"

using namespace sf;

class GamePlay
{
public:
	GamePlay();
	void gameLoop(RenderWindow* window);
private:
	void openShot(RenderWindow*, std::shared_ptr<Player> player);
	sf::RectangleShape m_backGround;
};
