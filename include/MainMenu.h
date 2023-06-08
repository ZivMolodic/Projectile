#pragma once
#include "Macros.h"
#include <SFML/Graphics.hpp>

class MainMenu {
public:
	MainMenu();
	void menuLoop(const sf::Vector2f& size);
private:
	void checkMouseOnButton(sf::RenderWindow* window, sf::Vector2f cursorLocation);
	sf::Texture m_logoTexture;
	sf::RectangleShape m_logo;
	std::vector<sf::Text> m_buttons;
	sf::RectangleShape m_backGround;
};