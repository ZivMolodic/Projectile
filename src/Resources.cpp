#include "Resources.h"
#include <vector>

Resources::Resources()
{
	loadGraphics();
	//loadSounds();
}

Resources& Resources::instance()
{
	static auto resources = Resources();
	return resources;
}

void Resources::loadGraphics()
{	
	std::vector <std::string> pngNames = { "menuBlock.png","boy.png" ,
		"main_background.png" ,"gameplay_background.png" ,
		"grenade.png", "grenade_launcher.png", "raft.png" };

	std::vector <char> pngChars = { 'B', 'r', 'm', 'b','*', 'g','#' };
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
