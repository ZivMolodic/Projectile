#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "RaftBlock.h"
#include "RaftMan.h"
#include "Weapon.h"

using namespace std;
class RaftMan;

class Player: public enable_shared_from_this<Player>
{
public:
    Player(int numOfRaftMen, const sf::Vector2f& position); /////////
    void update();
    void draw(sf::RenderWindow* window);
    void getWeapon(RaftMan& pawn, int i);
    void done(RaftMan& pawn) { m_playing = false; }
    void play(RenderWindow* window, const sf::Event& event);
    bool isPlaying() const { return m_playing; }
    bool shooting() { auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); }); return search != m_weapons.end(); }
    sf::Vector2f getObjectilePosition() 
    {
        auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
        if (search != m_weapons.end())
            return search->get()->getObjectilePosition();

    }
    //void handleCollision(const RectangleShape& rec)
    //{
    //    auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
    //    if (search != m_weapons.end())
    //        search->get()->handleCollision(rec);

    //}

private:
    void initRaftMen();


    vector<std::unique_ptr<RaftBlock>> m_raft;
    vector<std::shared_ptr<Weapon>> m_weapons;
    vector<RaftMan> m_raftMen;
    bool m_playing;
    int m_crewSize;
    sf::Vector2f m_position;
};