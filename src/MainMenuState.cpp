#include "MainMenuState.h"
#include "HelpScreenState.h"
#include "LevelSelectState.h"

MainMenuState::MainMenuState(std::shared_ptr<GameTools> gameTools, bool newAloc)
	:m_gameTools(gameTools), m_newAlloc(newAloc)
{
	initilaize();
}

void MainMenuState::processManeger()
{
	if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_gameTools->m_window.getWindow().close();
			break;


		case sf::Event::MouseButtonReleased:
		{
			auto location = m_gameTools->m_window.getWindow().mapPixelToCoords(
				{ event.mouseButton.x, event.mouseButton.y });
			
			m_mode = handleClick(location);
			m_event = true;
			break;
		}
		}
	}
}

void MainMenuState::update()
{
	if(m_event)
		menuManeger();
}

void MainMenuState::Draw()
{
	m_gameTools->m_window.getWindow().clear();
	drawMenu();
	m_gameTools->m_window.getWindow().display();
}

void MainMenuState::Resume()
{
	setSoundTexture(m_soundButton);
}

void MainMenuState::initilaize()
{
	m_backGround.setTexture(&GameResources::getInstance().getBackGroundScreens(backGrounds::MENU));
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);

	float delta{ 0 };

	//menu buttuns
	for (size_t i = 0; i < 3; i++)
	{
		m_buttons.emplace_back();
		m_buttons.back().setTexture(&GameResources::getInstance().getMenuTexture(i));
		m_buttons.back().setSize(m_backGround.getSize() * 0.2f);
		m_buttons.back().setOrigin(m_buttons.back().getSize() * 0.5f);
		m_buttons.back().setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT * 0.4 + delta);
		delta += m_backGround.getSize().x * 0.12f;
	}

	//sound buttun

	m_soundButton.setRadius(50.f);
	m_soundButton.setOrigin(m_soundButton.getRadius(),m_soundButton.getRadius());
	m_soundButton.setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100);
	setSoundTexture(m_soundButton);
}

menuCommand MainMenuState::handleClick(const sf::Vector2f& mouse_loc) 
{
	if (m_soundButton.getGlobalBounds().contains(mouse_loc)) 
		return (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE ? menuCommand::SOUND : menuCommand::MUTE);

	for (size_t i = 0; i < m_buttons.size(); i++)
		if (m_buttons.at(i).getGlobalBounds().contains(mouse_loc))
			return static_cast<menuCommand>(i);

	return menuCommand::DEFAULT;
}

void MainMenuState::menuManeger()
{
	switch (m_mode)
	{
	case menuCommand::PLAY:     if (m_newAlloc)m_gameTools->m_gameStates.addState(std::make_unique<LevelSelectState>(this->m_gameTools), true);
								else m_gameTools->m_gameStates.removeState();																		break;
	case menuCommand::HELP:     m_gameTools->m_gameStates.addState(std::make_unique<HelpScreenState>(this->m_gameTools), false);				    break;
	case menuCommand::MUTE:;
	case menuCommand::SOUND:    soundButtonClicked(m_soundButton);                                                                                  break;
	case menuCommand::EXIT:     m_gameTools->m_window.getWindow().close();																			break;
	default:																																		break;
	}
	m_event = false;
}

void MainMenuState::drawMenu()
{
	m_gameTools->m_window.getWindow().draw(m_backGround);
	for (size_t i = 0; i < m_buttons.size(); i++)
		m_gameTools->m_window.getWindow().draw(m_buttons.at(i));
	m_gameTools->m_window.getWindow().draw(m_soundButton);
}
