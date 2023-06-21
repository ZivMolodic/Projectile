#include "Button.h"
#include "GamePlay.h"

using namespace sf;

Button::Button(Vector2f position, Vector2f size, char c, std::string text)
	:m_position(position), m_text(text, Resources::instance().getFont())
{
	m_text.setPosition(position);
	m_text.setCharacterSize(50);
	m_text.setOrigin(m_text.getLocalBounds().width / 2.f, m_text.getLocalBounds().height / 2.f);
	m_text.setFillColor(sf::Color::White);
	m_text.setOutlineThickness(4);
	m_text.setOutlineColor(sf::Color::Black);

	m_picture.setTexture(&Resources::instance().getTexture(c));
	m_picture.setSize(size);
	m_picture.setPosition(position);
	m_picture.setOrigin(m_picture.getSize() / 2.f);
}

void Button::draw(RenderWindow* window, sf::Vector2f cursorLocation)
{ 
	m_picture.setScale(1, 1);

	if (m_picture.getGlobalBounds().contains(cursorLocation))
		m_picture.setScale(1.3, 1.3);

	window->draw(m_picture); 
	window->draw(m_text);
}


PlayButton::PlayButton(Vector2f position, Vector2f size, char c, std::string text)
	:Button(position, size, c, text) {}

void PlayButton::play(RenderWindow* window)
{
	auto gamePlay = GamePlay();
	gamePlay.gameLoop(window);
}

HelpButton::HelpButton(Vector2f position, Vector2f size, char c, std::string text)
	:Button(position, size, c, text) {}

void HelpButton::play(RenderWindow* window)
{
	window->close();
	exit(EXIT_SUCCESS);
}