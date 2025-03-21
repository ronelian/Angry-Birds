#include "Game.h"
#include "MainMenuState.h"
#include "LevelSelectState.h"


Game::Game()
	:m_gameTools(std::make_shared<GameTools>())
{
	m_gameTools->m_gameStates.addState(std::make_unique<MainMenuState>(this -> m_gameTools, true), true); //create the first state of the game - the menu
}

void Game::runGame()
{
	//in each iteration process according to the state
	while (m_gameTools->m_window.getWindow().isOpen())
	{
		m_gameTools->m_gameStates.checkForUpdates();
		m_gameTools->m_gameStates.getCurrentState()->processManeger();
		m_gameTools->m_gameStates.getCurrentState()->update();
		m_gameTools->m_gameStates.getCurrentState()->Draw();
	}
}
