#include "Player.h"

Player::Player(int numOfRaftMen, const sf::Vector2f& position, Board* board)
	: m_playing(false), m_crewSize(numOfRaftMen), m_position(position), m_board(board)
{
	auto raft = new RaftBlock(position);
	m_raft.emplace_back(raft);
	m_board->addObject(raft);

	raft = new RaftBlock({ position.x, position.y - 90});
	m_raft.emplace_back(raft);
	m_board->addObject(raft);

	raft = new RaftBlock({ position.x + 100, position.y - 90 });
	m_raft.emplace_back(raft);
	m_board->addObject(raft);
	
	initRaftMen();
	//for(int i=0; i < 3; ++i)
	//	for(int j = 0; j < 2; ++j)
	//		m_raft.emplace_back(std::make_shared<RaftBlock>(sf::Vector2f{ BACKGROUND_SIZE.x - i*163, position.y - 350*j }));
	//for (int i = 1; i < 6; ++i)
	//	m_raft.emplace_back(std::make_shared<RaftBlock>(sf::Vector2f{ position.x + i * 163, position.y }));
	//std::unique_ptr<GameObject> p;
	//auto weapon = new Weapon();
	m_weapons.emplace_back(std::make_shared<Weapon>());
}

void Player::initRaftMen()
{
	for (int i = 0; i < m_crewSize; ++i)
	{
		auto self = this;
		auto raftMan = new RaftMan(self, sf::Vector2f(m_position.x, m_position.y - 20));
		m_raftMen.emplace_back(raftMan);
		m_board->addObject(raftMan);
	}
}

void Player::update()
{
	////cause raftMan uses shared_from_this
	//static bool raftMenInit = false;
	//if (!raftMenInit)
	//{
	//	initRaftMen();
	//	raftMenInit = true;
	//}


	for (auto& pawn : m_raftMen)
	{
		pawn->update();
		//for(const auto& raft: m_raft)
		//	pawn.handleCollision(raft->getRec());
		//pawn.handleCollision(m_raft[0]->getRec());
	}
	for (auto& x : m_weapons) 
		x->update();

	//auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
	//    if (search != m_weapons.end())
	//		for(const auto& rec: m_raft)
	//			search->get()->handleCollision(rec->getRec());
	//for (const auto& x : m_raft)
		//handleCollision(x->getRec());

}

void Player::draw(sf::RenderWindow* window)
{
	//for (const auto& x : m_raft)
	//	x->draw(window);

	//for (const auto& x : m_raftMen)
	//	x->draw(window);
	//for (const auto& x: m_raftMen)
	//	if(x->)

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
	m_raftMen[0]->play(window, event);
}

sf::Vector2f Player::getPlayerPosition() const
{
	return m_raftMen[rand() % m_raftMen.size()]->getPosition();
}

void Computer::play(RenderWindow* window, const sf::Event& event)
{
	if(!isPlaying())
	{
		//illustrates computer thinking
		//sf::Clock timer;
		//timer.restart();
		//while (timer.getElapsedTime().asSeconds() < 2.f);

		setPlay();
		m_playerPosition = getBoard()->getPlayerPosition();
		m_turn = (m_turn+1) % m_raftMen.size();
		//m_destination = m_raft[rand() % m_raft.size()]->getPosition();
		m_destination = m_raft[2]->getPosition();
	}
	
	if (std::abs(m_raftMen[m_turn]->getPosition().y - m_destination.y + m_raftMen[m_turn]->getRec().height) > 1 ||
		std::abs(m_raftMen[m_turn]->getPosition().x - m_destination.x) > 1)
			walk(m_destination, window, event, m_turn);
}

void Computer::walk(const sf::Vector2f& destination, RenderWindow* window, const sf::Event& event, int turn)
{
	if(destination.y < m_raftMen[turn]->getPosition().y)
		for(auto& raft: m_raft)
			if(std::abs(raft->getPosition().x - m_raftMen[turn]->getPosition().x) < 1)
			{
				m_raftMen[turn]->play(window, event, Direction::Up);
				break;
			}

	if (m_raftMen[turn]->getPosition().x < destination.x)
		m_raftMen[turn]->play(window, event, Direction::Right);
	
	else if (m_raftMen[turn]->getPosition().x > destination.x)
		m_raftMen[turn]->play(window, event, Direction::Left);

	//else if (m_raftMen[turn]->getPosition().y > destination.y + m_raftMen[turn]->getRec().height)
	//	m_raftMen[turn]->play(window, event, Direction::Up);
}