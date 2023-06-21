#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "Resources.h"

using namespace sf;

class Button
{
public:
	Button(Vector2f position, Vector2f size, char c, std::string text = "");
	~Button() = default;
	virtual void play(RenderWindow* window) = 0;
	FloatRect globalBounds() const { return m_picture.getGlobalBounds(); }
	void draw(RenderWindow* window, sf::Vector2f cursorLocation); 
private:
	Vector2f m_position;
	Text m_text;
	RectangleShape m_picture;
};

class PlayButton : public Button
{
public:
	PlayButton(Vector2f position, Vector2f size, char c, std::string text = "");
	void play(RenderWindow* window) override;
};

class HelpButton : public Button
{
public:
	HelpButton(Vector2f position, Vector2f size, char c, std::string text = "");
	void play(RenderWindow* window) override;
};

class UpRaftButton : public Button
{
public:
	UpRaftButton(Vector2f position, Vector2f size, char c)
		:Button(position, size, c) {}
	void play(RenderWindow* window) override {};
};