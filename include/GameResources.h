#pragma once

#include <iostream>
#include <vector>
#include <array>

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Macro.h"

class GameResources
{
public:
	static GameResources& getInstance();
	GameResources(const GameResources&) = delete; //disable copy constructor
	GameResources operator=(const GameResources&) = delete; //disable assimenget operator

	sf::Texture& getMenuTexture(const int& index);
	sf::Texture& getHelpTexture(const int& index);
	sf::Texture& getBirdTexture(const int& index);
	sf::Texture& getRogatkaTexture(const int& index);
	//sf::Texture& getPigsTexture(const int& index);
	sf::Texture& getPoofTexture(const int& index);
	sf::Texture& getLock();
	sf::Texture& getTransitionScreensState(const TransitionScreen&);
	sf::Texture& getObstacleTexture(const int& index);
	sf::Texture& getButtons(const int& index);
	sf::Texture& getLevelsFields(const int& index);
	sf::Texture& getBackGroundScreens(const backGrounds&);

	void playBackGroundMusic();

	musicCommand getMusicStatus() const;
	sf::Font& getFont(const int& index);
	sf::Text& createText(const std::string &, const sf::Color &, const int&);

private:
	//constructor/ distructor
	GameResources();
	~GameResources() = default;

	//members
	sf::Texture m_spriteSheet;
	sf::Texture m_lock;

	std::array <sf::Texture, 3> m_menuTexture;
	std::array <sf::Texture, 4> m_helpScreenTexture;//for state
	std::array <sf::Texture,3> m_backGround;
	std::array <sf::Texture,4> m_birdsTexture;
	std::array <sf::Texture,2> m_rogatkaTexture;
	std::array <sf::Texture, 5> m_poofTexture;
	std::array <sf::Texture, 2> m_transitionScreensState;
	std::array <sf::Texture, 5> m_buttons;
	std::array <sf::Texture, 20> m_obstacles;
	std::array <sf::Texture, 6> m_levelsFields;
	std::array <sf::Font, 2> m_font;

	sf::SoundBuffer m_BackGroundBuffer;
	sf::Sound m_BackGroundSound;


	sf::Text m_text;
	
	//func
	void initTextures();
	void initFonts();
	void initSounds();
};