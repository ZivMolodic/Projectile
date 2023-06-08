#pragma once
#include "MainMenu.h"
#include "Resources.h"
#include "Macros.h"
#include "GameObject.h"
#include "GamePlay.h"
#include "RaftBlock.h"
#include <memory>

MainMenu::MainMenu()
    : m_buttons({ sf::Text("PLAY", Resources::instance().getFont()),
                //sf::Text("PLAY PRO", Resources::instance().getFont()),
                sf::Text("HELP", Resources::instance().getFont()),
                sf::Text("EXIT", Resources::instance().getFont()) })
{

    float y = BUTTONS_POSITION.y;
    float spaceBetweenButton = (WINDOW_SIZE.y - SPACE_WITHOUT_BUTTONS * 2.f) / (m_buttons.size() - 1);
    for (int i = 0; i < m_buttons.size(); i++)
    {
        m_buttons[i].setPosition({ BUTTONS_POSITION.x , y });
        y += spaceBetweenButton;
        m_buttons[i].setFillColor(sf::Color::White);
        m_buttons[i].setOutlineThickness(1.5);
        m_buttons[i].setOutlineColor(sf::Color::Black);
    }

    m_backGround.setTexture(&Resources::instance().getTexture('m'));
    m_backGround.setSize(WINDOW_SIZE);
}



void MainMenu::menuLoop(const sf::Vector2f& size)
{
    auto window = sf::RenderWindow(sf::VideoMode(size.x, size.y), "Raft Wars");
    while (window.isOpen())
    {
        window.clear();
        window.draw(m_backGround);

        auto cursorLocation = sf::Vector2f({ sf::Mouse::getPosition(window).x * 1.f,
                                                sf::Mouse::getPosition(window).y * 1.f });

        checkMouseOnButton(&window, cursorLocation);

        window.display();

        for (auto event = sf::Event{}; window.pollEvent(event); )
        {
            switch (event.type)
            {
            case sf::Event::Closed:
            {
                window.close();
                break;
            }

            case sf::Event::MouseButtonReleased:
            {

                switch (event.mouseButton.button)
                {
                case sf::Mouse::Left:
                {

                    if (m_buttons[0].getGlobalBounds().contains(cursorLocation))
                    {
                        auto gamePlay = GamePlay();
                        gamePlay.gameLoop(&window);
                    }
                        

                    else if (m_buttons[1].getGlobalBounds().contains(cursorLocation))
                        ;

                    else if (m_buttons[2].getGlobalBounds().contains(cursorLocation))
                        ;

                    else if (m_buttons[3].getGlobalBounds().contains(cursorLocation))
                    {
                        window.close();
                        break;
                    }

                    
                    break;
                }
                }
            }
            }
        }
    }
}


void MainMenu::checkMouseOnButton(sf::RenderWindow* window, sf::Vector2f cursorLocation)
{
    for (int i = 0; i < m_buttons.size(); i++)
    {
        m_buttons[i].setScale(1.5, 1.5);

        if (m_buttons[i].getGlobalBounds().contains(cursorLocation))
            m_buttons[i].setScale(2.0, 2.0);


        m_buttons[i].setOrigin(m_buttons[i].getLocalBounds().width / 2.f,
            m_buttons[i].getLocalBounds().height / 2.f);
        window->draw(m_buttons[i]);
    }
}

