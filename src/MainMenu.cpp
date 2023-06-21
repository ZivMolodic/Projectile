#pragma once
#include "MainMenu.h"
#include "Resources.h"
#include "Macros.h"
#include "GameObject.h"
#include "GamePlay.h"
#include "RaftBlock.h"
#include <iostream>
#include <cstdlib>
#include <memory>

MainMenu::MainMenu()
{
    float y = BUTTONS_POSITION.y;
    //le'adken et mispar hakaftorim
    float spaceBetweenButton = (WINDOW_SIZE.y - SPACE_WITHOUT_BUTTONS * 2.f) / (2 - 1);

    m_buttons.push_back(std::make_unique<PlayButton>(
        Vector2f{ BUTTONS_POSITION.x , y }, Vector2f{ 200, 70 }, 'B', "PLAY"));
    y += spaceBetweenButton;
    m_buttons.push_back(std::make_unique<HelpButton>(
        Vector2f{ BUTTONS_POSITION.x , y }, Vector2f{ 200, 70 }, 'B', "EXIT"));

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

        for (auto const& button : m_buttons)
            button->draw(&window, cursorLocation);

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
                    for(auto const& button : m_buttons)
                        if (button->globalBounds().contains(cursorLocation))
                        {
                            button->play(&window);
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

