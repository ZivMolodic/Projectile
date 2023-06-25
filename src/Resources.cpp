#include "Resources.h"
#include <vector>
#include "Direction.h"

namespace
{
    AnimationData MissileData()
    {
        const auto size = sf::Vector2i(40, 40);
        const auto initSpace = sf::Vector2i(1, 2);
        const auto middleSpace = sf::Vector2i(0, 10);

        auto missile = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        missile.m_data[Direction::Right].emplace_back(currentStart, size);
        missile.m_data[Direction::Right].emplace_back(nextStart(), size);
        missile.m_data[Direction::Down].emplace_back(nextStart(), size);
        missile.m_data[Direction::Down].emplace_back(nextStart(), size);
        missile.m_data[Direction::Left].emplace_back(nextStart(), size);
        missile.m_data[Direction::Left].emplace_back(nextStart(), size);
        missile.m_data[Direction::Up].emplace_back(nextStart(), size);
        missile.m_data[Direction::Up].emplace_back(nextStart(), size);

        return missile;
    }

    AnimationData GuidedMissileData()
    {
        const auto size = sf::Vector2i(40, 40);
        const auto initSpace = sf::Vector2i(851, 2);
        const auto middleSpace = sf::Vector2i(0, 10);

        auto guidedMissile = AnimationData{};
        auto currentStart = initSpace;

        auto nextStart = [&]()
        {
            currentStart += middleSpace;
            currentStart.y += size.y;
            return currentStart;
        };

        guidedMissile.m_data[Direction::Right].emplace_back(currentStart, size);
        guidedMissile.m_data[Direction::Right].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Right].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Down].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Down].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Down].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Left].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Left].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Left].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Up].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Up].emplace_back(nextStart(), size);
        guidedMissile.m_data[Direction::Up].emplace_back(nextStart(), size);

        return guidedMissile;
    }
}

Resources::Resources()
    :m_animation(MAX)
{
	loadGraphics();
	//loadSounds();
    m_animation[Missile] = MissileData();
    m_animation[GuidedMissile] = GuidedMissileData();
}

Resources& Resources::instance()
{
	static auto resources = Resources();
	return resources;
}

void Resources::loadGraphics()
{	 
	std::vector <std::string> pngNames = { "guided_missile.png",
        "missile.png", "down_raft_button.png",
			 "tennis_button.png", "up_raft_button.png",
			"guided_missile_button.png","grenade_button.png"
		,"missile_button.png", "menuBlock.png","boy.png" ,
		"main_background.png" ,"gameplay_background.png" ,
		"grenade.png", "grenade_launcher.png", "raft.png", "up_raft.png", "explosion.png"};

	std::vector <char> pngChars = {'S','s', 'd', 'T', 'U','M', 'G', 't', 'B', 'r', 'm', 'b','*', 'g','#', 'u', 'x'};
	sf::RenderWindow window;
	for (int i = 0; i < pngNames.size(); i++)
	{
		auto texture = sf::Texture();
		//texture.loadFromFile(pngNames[i]);
		//texture.setSmooth(true);
		m_textures.insert({ pngChars[i], texture });
		m_textures[pngChars[i]].loadFromFile(pngNames[i]);
		m_textures[pngChars[i]].setSmooth(true);
	}

	m_font.loadFromFile("C:/Windows/Fonts/Bauhs93.ttf");
}

sf::Texture & Resources::getTexture(char c)
{
	if (auto search = m_textures.find(c); search != m_textures.end())
		return m_textures[c];
}

//void Resources::loadSounds()
//{
//	char sounds[][20] = { "timer.wav", "finish_level.wav", "game_over.wav", "pacman_dead.wav",
//						  "ghost_eaten.wav", "present.wav", "eat_cookie.wav", "door_open.wav" };
//
//	for (int i = 0; i < 8; i++)
//	{
//		sf::SoundBuffer sound;
//		sound.loadFromFile(sounds[i]);
//		m_sounds.push_back(sound);
//	}
//
//	m_backGround.openFromFile("background.wav");
//}
//
//
//void Resources::playMusic(enum Sounds i, int vol)
//{
//	m_backGround.setVolume(0);
//	m_sound.setBuffer(m_sounds[i]);
//	m_sound.setVolume(vol);
//	m_sound.play();
//	m_backGround.setVolume(50);
//}
//
//void Resources::playBackGround()
//{
//	m_backGround.setVolume(50);
//	m_backGround.play();
//}
//
//void Resources::volumeBackGround(int vol)
//{
//	m_backGround.setVolume(vol);
//}
//
//void Resources::stopBackGroundMusic()
//{
//	m_backGround.stop();
//}

