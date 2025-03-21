#pragma once

#include <utility>

#include "Macro.h"
#include "Game.h"
#include "Bird.h"
#include "Ground.h"
#include "World.h"

#include "Rogatka.h"
#include "MyContactListener.h"
#include "YellowBird.h"
#include "RedBird.h"
#include "LevelManager.h"
#include "BlueBird.h"
#include "Obstacle.h"
#include "BlackBird.h"

#include "GuideLine.h"

struct poof {

	poof(const sf::Vector2f& pos) : m_pos{pos} { ; }
	sf::Vector2f m_pos;
	sf::Clock m_clock;
	sf::Time elapsedTime() { return m_clock.getElapsedTime(); };
};

struct SharedData; 

class PlayState :public State
{
public:
	PlayState(std::shared_ptr<GameTools>, std::shared_ptr<SharedData>);
	~PlayState() = default;

	//virtual funcs
	virtual void processManeger()override;
	virtual void update()override;
	virtual void Draw()override;
	virtual void Resume()override;

	//update func
	void deleteObj();
	void drawGame();
	void drawDestroyedObj();
	void updateView();
	void setNextBird(const bool &x);
	void setUpForEndLevel(std::string,const TransitionScreen&);
	bool levelEnd();
	bool isFinishedMoving();
	void updateDataPosition();
	void setScore(const int&);
	void checkIfButtonPressed(const sf::Event&,const sf::Vector2f&);
	void Restart();
	void Back();
	void levelIntroduction();

protected:
	void initilaize();
	
private:
	std::shared_ptr<GameTools> m_gameTools;
	sf::RectangleShape m_backGround;

	std::array<std::unique_ptr<StaticObjects>, 2> m_worldObjects;
	std::vector<std::unique_ptr<Bird>> m_birds;
	std::vector<std::unique_ptr<StaticObjects>> m_pigs;
	std::vector<std::unique_ptr<StaticObjects>> m_gameObjects;
	std::vector<std::pair<sf::Text, sf::Text>> m_levelData;
	std::unique_ptr<MyContactListener> m_contactListener;
	std::vector<sf::CircleShape> m_buttons;

	//destroy's animation array
	std::array<sf::RectangleShape, 3> m_destroyAnimation;
	std::vector<poof>m_poofsContainer;

	//init functions
	std::shared_ptr<World> m_world;
	std::shared_ptr<SharedData> m_sharedData;//shared data with other states
	LevelManager m_lvlsMngr;

	//init funcs
	void createGroundAndRogatka();
	void createLevelData();

	bool m_levelIntroduction;
};


