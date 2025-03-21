#include "TransitionScreensState.h"

TransitionScreens::TransitionScreens(std::shared_ptr<GameTools> gameTools, const TransitionScreen& texture)
	:m_gameTools(gameTools), m_stateTimeLimit(3), m_texture(texture)
{
	initilaize();
}

void TransitionScreens::processManeger()
{
	if (auto event = sf::Event{}; m_gameTools->m_window.getWindow().pollEvent(event))
	{
		if(event.type == sf::Event::Closed)
			m_gameTools->m_window.getWindow().close();
	}

	sf::Time elapsed = m_stateClock.restart();
	m_stateTimeLimit -= (elapsed.asSeconds() / 1.5);
}

void TransitionScreens::update()
{
	if (m_stateTimeLimit <= 0)
	{
		m_gameTools->m_gameStates.removeState();
		m_gameTools->m_gameStates.switchStates();
	}

}

void TransitionScreens::Draw()
{
	m_gameTools->m_window.getWindow().clear();
	m_gameTools->m_window.getWindow().draw(m_TransitionScreen);
	m_gameTools->m_window.getWindow().display();
}

void TransitionScreens::initilaize()
{
	m_TransitionScreen.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_TransitionScreen.setPosition(sf::Vector2f(0, 0));
	m_TransitionScreen.setTexture(&GameResources::getInstance().getTransitionScreensState(m_texture));
}
