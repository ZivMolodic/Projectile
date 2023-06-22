#pragma once
#include "SFML/Graphics.hpp"
#include <vector>
#include <memory>
#include "Board.h"
#include "RaftBlock.h"
#include "RaftMan.h"
#include "Weapon.h"

using namespace std;
class RaftMan;

class Player
{
public:
    Player(int numOfRaftMen, const sf::Vector2f& position, Board* board);
    void update();
    void draw(sf::RenderWindow* window);
    void getWeapon(RaftMan& pawn, int i);
    std::shared_ptr<GameObject> getObjectile() { for (const auto& x : m_weapons) if (x->firing())return x->getObjectile(); }
    void done(RaftMan& pawn) { m_playing = false; }
    virtual void play(RenderWindow* window, const sf::Event& event);
    bool isPlaying() const { return m_playing; }
    bool shooting() { auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); }); return search != m_weapons.end(); }
    sf::Vector2f getObjectilePosition() 
    {
        auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
        if (search != m_weapons.end())
            return search->get()->getObjectilePosition();

    }
    sf::Vector2f getPlayerPosition() const;
    //void handleCollision(const RectangleShape& rec)
    //{
    //    auto search = find_if(m_weapons.begin(), m_weapons.end(), [](std::shared_ptr<Weapon> w) { return w->firing(); });
    //    if (search != m_weapons.end())
    //        search->get()->handleCollision(rec);

    //}
protected:
    Board* getBoard() { return m_board; }
    vector<std::unique_ptr<RaftBlock>> m_raft;
    vector<std::unique_ptr<RaftMan>> m_raftMen;
private:
    void initRaftMen();

    Board* m_board;
    vector<std::shared_ptr<Weapon>> m_weapons;
    bool m_playing;
    int m_crewSize;
    sf::Vector2f m_position;
};

class Computer: public Player
{
public:
    void play(RenderWindow* window, const sf::Event& event) override;

private:
    void walk(const sf::Vector2f& destination);
};