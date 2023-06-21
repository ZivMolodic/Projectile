#include "RaftMan.h"
#include "Player.h"

RaftMan::RaftMan(std::weak_ptr<Player> team, const sf::Vector2f& position)
	: DynamicObject({30,60},position,'r',0.5,2), m_team(team),
	m_life(100), m_jumps(false), m_holdRaft(false), m_raftBlock(Vector2f{ -1,-1 })
{}

void RaftMan::update()
{ 
	m_physics->update(m_shape);

	if (m_weapon.lock())
		m_weapon.lock()->setPosition(getPosition());
}

void RaftMan::draw(sf::RenderWindow* window, const sf::Vector2f& position) const
{
	window->draw(*m_shape);
	if (m_weapon.lock())
		m_weapon.lock()->draw(window, { m_shape->getPosition().x, getPosition().y + 5 });
	if (m_holdRaft)
		m_raftBlock.draw(window);
}

void RaftMan::play(sf::RenderWindow* window, const sf::Event& event)
{

	m_physics->setWalking(false);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_shape->setScale({ -1,1 });
		if (m_physics->isJumping())
			m_physics->setVelocity({ -1.5f,m_physics->getVelocity().y });
		else
		{
			//m_shape->move({ 1,0 });
			m_physics->setVelocity({ -1,0 });
			m_physics->setWalking(true);
		}
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_shape->setScale({ 1,1 });
		if(m_physics->isJumping())
			m_physics->setVelocity({ 1.5f,m_physics->getVelocity().y});
		else
		{
			//m_shape->move({ 1,0 });
			m_physics->setVelocity({ 1,0 });
			m_physics->setWalking(true);
		}
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !m_physics->isJumping())
	{
		m_physics->setJumping(true);
		m_physics->setVelocity({ 0, -12 });
	}

	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		m_holdRaft = true;
		m_raftBlock.setPosition(Vector2f{ sf::Mouse::getPosition(*window) });
		m_raftBlock.setBlendMode();
		m_team.lock()->placeRaft(m_raftBlock, sf::Mouse::getPosition(*window));
	}

	else if (event.type == sf::Event::MouseButtonReleased)
		//else if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_weapon.lock())
	{
		if (m_weapon.lock() && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window); // Get the global mouse position
			sf::Vector2f localPosition = window->mapPixelToCoords(mousePosition); // Convert to local coordinates

			m_weapon.lock()->shot((localPosition - m_shape->getPosition()) * 0.06f);
			m_weapon.lock() = nullptr;
			m_team.lock()->done(*this);
		}
		else if (event.mouseButton.button == sf::Mouse::Button::Right)
			m_team.lock()->getWeapon(*this, 0);

		else if (m_holdRaft && event.mouseButton.button == sf::Mouse::Button::Left)
		{
			if (m_team.lock()->placeRaft(m_raftBlock, sf::Mouse::getPosition(*window)))
			{
				m_team.lock()->addRaft(*this);
				m_holdRaft = false;
			}
		}
	}
	else if (m_holdRaft)
	{
		m_raftBlock.setPosition(Vector2f{ sf::Mouse::getPosition(*window) });
		m_team.lock()->placeRaft(m_raftBlock, sf::Mouse::getPosition(*window));
	}
}

void RaftMan::handleCollision(const sf::RectangleShape& rec)
{
	if (m_physics->isJumping() && m_physics->getVelocity().y < 0)
		return;
	if (auto update = m_physics->manageCollision(m_shape->getPosition(), rec); update != sf::Vector2f(0, 0))
	{
		m_physics->setJumping(false);
		m_shape->setPosition(update);
	}
}
