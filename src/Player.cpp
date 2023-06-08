#include "Player.h"

Player::Player(int numOfRaftMen, const sf::Vector2f& position)
	: m_playing(false), m_crewSize(numOfRaftMen), m_position(position)
{
	m_raft.emplace_back(std::make_unique<RaftBlock>(position));

	for(int i=0; i < 6; ++i)
		for(int j = 0; j < 2; ++j)
			m_raft.emplace_back(std::make_unique<RaftBlock>(sf::Vector2f{ BACKGROUND_SIZE.x - i*163, position.y - 350*j }));
	//for (int i = 1; i < 6; ++i)
	//	m_raft.emplace_back(std::make_unique<RaftBlock>(sf::Vector2f{ position.x + i * 163, position.y }));


	m_weapons.emplace_back(std::make_shared<Weapon>());
}

void Player::initRaftMen()
{
	for (int i = 0; i < m_crewSize; ++i)
	{
		auto self = this->shared_from_this();
		m_raftMen.emplace_back(RaftMan(self, sf::Vector2f(m_position.x, m_position.y - 60)));
	}
}

void Player::update()
{
	//cause raftMan uses shared_from_this
	static bool raftMenInit = false;
	if (!raftMenInit)
	{
		initRaftMen();
		raftMenInit = true;
	}

	for (auto& pawn : m_raftMen)
		pawn.update();

	for (auto& x : m_weapons) 
		x->update();

	auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
	    if (search != m_weapons.end())
			for(const auto& rec: m_raft)
				search->get()->handleCollision(rec->getRec());
	//for (const auto& x : m_raft)
		//handleCollision(x->getRec());

}

void Player::draw(sf::RenderWindow* window)
{
	for (const auto& x : m_raft)
		x->draw(window);

	for (const auto& x : m_raftMen)
		x.draw(window);

}

void Player::getWeapon(RaftMan& pawn, int i)
{
	i++;
	//needs to manage enabling
	std::shared_ptr wp = (m_weapons[i % m_weapons.size()]);
	//std::shared_ptr wp = m_weapons.at(0);
	pawn.useWeapon(wp);
}

void Player::play(RenderWindow* window, const sf::Event& event)
{
	//needs to manage internal turns
	m_playing = true;
	m_raftMen[0].play(window, event);
}
