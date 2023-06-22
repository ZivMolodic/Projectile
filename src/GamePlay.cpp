#include "GamePlay.h"
#include "Resources.h"
#include "Macros.h"


GamePlay::GamePlay()
{
    m_backGround.setTexture(&Resources::instance().getTexture('b'));
    m_backGround.setSize(BACKGROUND_SIZE);
    m_backGround.setPosition({ 0,0 });
}

void GamePlay::gameLoop(RenderWindow* window)
{
    auto board = Board(Vector2f{ 180, 400 }, Vector2f{ 380,400 }, 1);
    //auto player = std::make_shared<Player>(1, Vector2f{ 180, 400 });

    bool playerTurn = true;

    auto view = sf::View(sf::FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));

    
    window->setFramerateLimit(30);
    //openShot(window, player);

    while (window->isOpen())
    {
        window->clear();
        window->setView(view);
        window->draw(m_backGround);
        //update
        board.update();
        board.handleCollisions();
        board.draw(window);
        //player->update();
        //player->draw(window);

        window->display();

        auto event = sf::Event{};
        while (window->pollEvent(event))
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window->close();
                break;
            }
            case sf::Event::KeyPressed:
            {
               // view = View(sf::FloatRect(window->getView().getCenter().x + 10, 0, 300, 600));
                break;
            }
            case sf::Event::KeyReleased:
                break;
            }
        }
       // view = window->getView();
        /*if(view.getCenter().x + view.getSize().x/2.f < m_backGround.getSize().x &&
            view.getCenter().x + view.getSize().x / 2.f > 0)
            view.move(Vector2f({ 1, 0 }) * 0.15f);*/
        board.play(window, event);
        //if (playerTurn)
        //{
        //    player->play(window, event);
        //    //playerTurn = false;
        //}
        //else if (player->isPlaying())
        //    player->play(window, event);
        

        //if (player->shooting())
        //{
        //    sf::Vector2f objPosition = player->getObjectilePosition();
        //    if (objPosition.x - view.getSize().x/2.f > 0 && objPosition.x + view.getSize().x/2.f <= m_backGround.getSize().x)
        //        view.setCenter({ objPosition.x, view.getCenter().y });
        //}
        //else
        //    view.setCenter({ view.getSize().x / 2.f , view.getCenter().y });

    }
}


void GamePlay::openShot(RenderWindow* window, std::shared_ptr<Player> player)
{
    auto view = sf::View(sf::FloatRect(0, 0, WINDOW_SIZE.x, WINDOW_SIZE.y));

    bool firstTime = true;
    
    while (window->isOpen())
    {
        window->clear();
        window->setView(view);
        window->draw(m_backGround);
        //player->draw(window);
        window->display();
        if (firstTime) {
            sleep(sf::seconds(1));
            firstTime = false;
        }
        view = window->getView();
        if (view.getCenter().x + view.getSize().x / 2.f < m_backGround.getSize().x &&
            view.getCenter().x + view.getSize().x / 2.f > 0)
            view.move(Vector2f({ 1, 0 }) * 0.3f);
        else {
            sleep(sf::seconds(1));
            break;
        }
    }
}
