#include "Board.h"
#include "Player.h"

Board::Board(const sf::Vector2f& playerPosition, const sf::Vector2f& computerPosition, int numOfRaftMen)
    : m_user(nullptr), m_computer(nullptr)
{
    // Create the Board object without initializing m_user and m_computer

    // Create the Players after the Board object is fully constructed
    m_user = std::make_shared<Player>(numOfRaftMen, playerPosition, this);
    m_user->update();
    m_computer = std::make_shared<Player>(numOfRaftMen, computerPosition, this);
    m_computer->update();
}


void Board::addObject(GameObject* object)
{
	//if(auto search = std::find(m_objects.begin(), m_objects.end(), *object); search == m_objects.end())
		m_objects.push_back(object);
    //m_objects.push_back(std::unique_ptr<GameObject>(object, deleteGameObject));
}

void Board::draw(RenderWindow* window) 
{ 
	for (auto& object : m_objects) object->draw(window);
}
void Board::play(RenderWindow* window, const sf::Event& event) 
{ 
	m_user->play(window, event); 
}