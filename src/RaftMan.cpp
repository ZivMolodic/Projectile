#include "RaftMan.h"
#include "Player.h"



RaftMan::RaftMan(Player* team, const sf::Vector2f& position)
	: DynamicObject({30,60},position,'r',0.5,2), m_team(team),
	m_life(100), m_jumps(false), m_holdRaft(false), m_raftBlock(nullptr),
	m_lastButton(NON)
{}

void RaftMan::update()
{ 
	m_physics->update(m_shape.get());

	if (m_weapon.lock())
	{
		m_weapon.lock()->setPosition(getPosition());
		m_weapon.lock()->update();
	}
}

void RaftMan::draw(sf::RenderWindow* window, const sf::Vector2f& position) const
{
	window->draw(*m_shape);
	if (m_weapon.lock())
		m_weapon.lock()->draw(window, { m_shape->getPosition().x, getPosition().y + 5 });
	if (m_holdRaft)
		m_raftBlock->draw(window);
}

void RaftMan::play(sf::RenderWindow* window, const sf::Event& event, const Direction& direction)
{
	Menu button = m_team->buttonPressed(window, event);
	
	raftManMove(window, event, direction);

	if (button == UP_RAFT || button == DOWN_RAFT)
		playWithRaft(button, window, event);

	else if (button != NON)
		playWithWeapon(button, window, event);

	m_lastButton = button;
}

void RaftMan::raftManMove(sf::RenderWindow* window, const sf::Event& event, const Direction& direction)
{
	m_physics->setWalking(false);
	m_physics->setVelocity({ 0 , m_physics->getVelocity().y });
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && direction == Direction::NA) || direction == Direction::Left)
	{
		m_shape->setScale({ -1,1 });
		if (m_physics->isJumping())
			m_physics->setVelocity({ -2.9f,m_physics->getVelocity().y });
		else
		{
			m_shape->move({ -1,0 });
			m_physics->setVelocity({ -0.5,0 });
			m_physics->setWalking(true);
		}
	}

	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && direction == Direction::NA) || direction == Direction::Right)
	{
		m_shape->setScale({ 1,1 });
		if(m_physics->isJumping())
			m_physics->setVelocity({ 2.9f,m_physics->getVelocity().y});
		else
		{
			m_shape->move({ 1,1 });
			m_physics->setVelocity({ 0.5,0 });
			m_physics->setWalking(true);
		}
	}
	else if (((sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && direction == Direction::NA) || direction == Direction::Up) && !m_physics->isJumping())
	{
		m_physics->setJumping(true);
		m_physics->setVelocity({ 0, -12 });
	}
}

void RaftMan::playWithRaft(const enum Menu& button, sf::RenderWindow* window, const sf::Event& event)
{
	if (m_holdRaft && event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if (m_lastButton != button) //needs to check if swap balls without shooting
		{
			m_weapon.reset();
			if (button == UP_RAFT)
			{
				std::unique_ptr<UpRaft> raftBlock = std::make_unique<UpRaft>(Vector2f{ sf::Mouse::getPosition(*window) });
				m_raftBlock = std::move(raftBlock);
			}

			else if (button == DOWN_RAFT)
			{
				std::unique_ptr<DownRaft> raftBlock = std::make_unique<DownRaft>(Vector2f{ sf::Mouse::getPosition(*window) });
				m_raftBlock = std::move(raftBlock);
			}
			m_raftBlock->setBlendMode();
			m_team->placeRaft(button, *m_raftBlock.get(), sf::Mouse::getPosition(*window));

		}

		else if (m_holdRaft && m_team->placeRaft(button, *m_raftBlock.get(), sf::Mouse::getPosition(*window)))
		{
			m_team->addRaft(*this, button);
			m_holdRaft = false;
		}
	}

	else if (!m_holdRaft)
	{
		m_weapon.reset();
		m_holdRaft = true;
		if (button == UP_RAFT)
		{
			std::unique_ptr<UpRaft> raftBlock = std::make_unique<UpRaft>(Vector2f{ sf::Mouse::getPosition(*window) });
			m_raftBlock = std::move(raftBlock);
		}

		else if (button == DOWN_RAFT)
		{
			std::unique_ptr<DownRaft> raftBlock = std::make_unique<DownRaft>(Vector2f{ sf::Mouse::getPosition(*window) });
			m_raftBlock = std::move(raftBlock);
		}
		m_raftBlock->setBlendMode();
		m_team->placeRaft(button, *m_raftBlock.get(), sf::Mouse::getPosition(*window));
	}

	else if (m_holdRaft)
	{
		m_raftBlock->setPosition(Vector2f{ sf::Mouse::getPosition(*window) });
		m_team->placeRaft(button, *m_raftBlock.get(), sf::Mouse::getPosition(*window));
	}
}

void RaftMan::playWithWeapon(const enum Menu& button, sf::RenderWindow* window, const sf::Event& event)
{
	if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Button::Left)
	{
		if(button != m_lastButton)
			m_team->getWeapon(*this, button);

		else if (m_weapon.lock())
		{
			sf::Vector2i mousePosition = sf::Mouse::getPosition(*window); // Get the global mouse position
			sf::Vector2f localPosition = window->mapPixelToCoords(mousePosition); // Convert to local coordinates

			m_weapon.lock()->shot((localPosition - m_shape->getPosition()) * 0.06f);
			m_weapon.lock() = nullptr;
			m_team->done(*this);
		}
	}
	else
	{
		m_holdRaft = false;
		m_team->getWeapon(*this, button);
	}
}
void RaftMan::shoot(const sf::Vector2f& velocity, const enum Menu& button)
{
	m_team->getWeapon(*this, button);
	m_weapon.lock()->shot(velocity, { m_shape->getPosition().x, getPosition().y + 5 });
}

void RaftMan::handleCollision(const sf::RectangleShape& rec)
{
	if (m_physics->isJumping() && m_physics->getVelocity().y < 0)
		return;
	else if (auto update = m_physics->manageCollision(m_shape->getPosition(), rec); update != sf::Vector2f(0, 0))
	{
		m_physics->setJumping(false);
		m_shape->setPosition(update);
	}
}

void RaftMan::handleExplosion(const Explosion& explosion)
{
	auto vec = this->getPosition() - explosion.getPosition();
	auto norm = std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	//m_life -= 1 / std::sqrtf(vec.x * vec.x + vec.y * vec.y);
	m_physics->setBounce(0.85f);
	m_physics->setVelocity((explosion.getLimitRadius() / norm) * (vec / norm));
}
