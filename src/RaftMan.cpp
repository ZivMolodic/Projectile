#include "RaftMan.h"
#include "Player.h"



RaftMan::RaftMan(std::weak_ptr<Player> team, const sf::Vector2f& position)
	: m_team(team), m_body({ 50,85 }), m_life(100),
	m_physics({ 50,85 }, 0.5f, 2.f), m_jumps(false)
{
	//m_physics.setBounce(0.75f);
	m_body.setOrigin(m_body.getSize() / 2.f);
	m_body.setPosition(position + (m_body.getSize() / 2.f));
	//m_body.setFillColor(sf::Color::Red);
	m_body.setTexture(&Resources::instance().getTexture('r'));
}

void RaftMan::draw(sf::RenderWindow* window) const
{
	window->draw(m_body);
	if (m_weapon.lock())
		m_weapon.lock()->draw(window, m_body.getPosition());
}

void RaftMan::play(sf::RenderWindow* window, const sf::Event& event)
{
	
	//if(event.type == sf::Event::KeyPressed)
	//{
	//	if (event.key.code == sf::Keyboard::Left)
	//		m_body.move(sf::Vector2f(-10.f, 0.f));

	//	else if (event.key.code == sf::Keyboard::Right)
	//	{
	//		m_body.move(10.f, 0.f);
	//	}
	//	else if (event.key.code == sf::Keyboard::Up)
	//		m_physics.setVelocity({ 0, -20 });
	//}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		m_body.move(sf::Vector2f(-7.f, 0.f));

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		m_body.move(7.f, 0.f);

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_jumps)
	{
		m_jumps = true;
		m_physics.setVelocity({ 0, -12 });
	}

	else if (event.type == sf::Event::MouseButtonReleased)
		//else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_weapon.lock())
	{
		if (m_weapon.lock() && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window); // Get the global mouse position
			sf::Vector2f localPosition = window->mapPixelToCoords(mousePosition); // Convert to local coordinates

			m_weapon.lock()->shot((localPosition - m_body.getPosition()) * 0.06f);
			m_weapon.lock() = nullptr;
			m_team.lock()->done(*this);
		}
		else if (event.mouseButton.button == sf::Mouse::Button::Right)
			m_team.lock()->getWeapon(*this, 0);
	}

}

void RaftMan::handleCollision(const sf::RectangleShape& rec)
{
	if (m_jumps && m_physics.getVelocity().y < 0)
		return;
	if (auto update = m_physics.manageCollision(m_body.getPosition(), rec); update != sf::Vector2f(0, 0))
	{
		m_jumps = false;
		m_body.setPosition(update);
	}
}
