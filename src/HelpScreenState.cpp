#include "HelpScreenState.h"

HelpScreenState::HelpScreenState(std::shared_ptr<GameTools> gameTools)
	:m_gameTools(gameTools), m_currentInstructionPage(0)
{
	initilaize();
}


void HelpScreenState::processManeger()
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

void HelpScreenState::update()
{
	if (m_event)
		helpManeger();
}

void HelpScreenState::Draw()
{
	m_gameTools->m_window.getWindow().clear();
	drawHelpScreen();
	m_gameTools->m_window.getWindow().display();
}

void HelpScreenState::initilaize()
{
	m_backGround.setTexture(&GameResources::getInstance().getHelpTexture(static_cast<int>(helpScreen::INSTRUCTION)));
	m_backGround.setSize(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
	m_backGround.setPosition(0, 0);

	//back to menu buttun
	m_backButton.setTexture(&GameResources::getInstance().getHelpTexture(static_cast<int>(helpScreen::BACK_BUTTON)));
	m_backButton.setSize(m_backGround.getSize() * 0.2f);
	m_backButton.setOrigin(m_backButton.getSize() * 0.5f);
	m_backButton.setPosition(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 100);

	//sound button 
	m_Buttons.emplace_back();
	m_Buttons.back().setRadius(50.f);
	m_Buttons.back().setOrigin(m_Buttons.back().getRadius(), m_Buttons.back().getRadius());
	m_Buttons.back().setPosition(WINDOW_WIDTH - 100, WINDOW_HEIGHT - 100);
	setSoundTexture(m_Buttons.back());

	//forward/backward buttons
	auto xPos = 50.f;
	for (int i = 1; i < 3; i++)
	{
		m_Buttons.emplace_back();
		m_Buttons.back().setRadius(30.f);
		m_Buttons.back().setOrigin(m_Buttons.back().getRadius(), m_Buttons.back().getRadius());
		m_Buttons.back().setPosition(xPos, WINDOW_HEIGHT/2);
		m_Buttons.back().setTexture(&GameResources::getInstance().getButtons(i + 2));
		xPos += WINDOW_WIDTH - 100;
	}
}

helpScreenCommand HelpScreenState::handleClick(const sf::Vector2f& mouse_loc)
{
	if (m_Buttons.at(0).getGlobalBounds().contains(mouse_loc))
		return (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE ? helpScreenCommand::SOUND : helpScreenCommand::MUTE);

	for (size_t i = 1; i < m_Buttons.size(); i++)
		if (m_Buttons.at(i).getGlobalBounds().contains(mouse_loc))
		{
			m_direction = i == 1 ? helpScreenCommand::BACKWARD : helpScreenCommand::FORWARD;
			return helpScreenCommand::INSTRUCTION;
		}
			

	if (m_backButton.getGlobalBounds().contains(mouse_loc))
		return helpScreenCommand::BACK;

	return helpScreenCommand::DEFAULT;
}

void HelpScreenState::helpManeger()
{
	switch (m_mode)
	{
	case helpScreenCommand::BACK:          m_gameTools->m_gameStates.removeState();        break;
	case helpScreenCommand::MUTE:;
	case helpScreenCommand::SOUND:         soundButtonClicked(m_Buttons.at(0));            break;
	case helpScreenCommand::INSTRUCTION:   moveBetweenPages();                             break;
	default:																	           break;
	}
	m_event = false;
}

void HelpScreenState::drawHelpScreen()
{
	m_gameTools->m_window.getWindow().draw(m_backGround);

	for (size_t i = 0; i < m_Buttons.size(); i++)
		m_gameTools->m_window.getWindow().draw(m_Buttons.at(i));

	m_gameTools->m_window.getWindow().draw(m_backButton);
}

void HelpScreenState::moveBetweenPages()
{

	if (m_direction == helpScreenCommand::FORWARD && m_currentInstructionPage + 1 < MAX_INSRUCTION_PAGES)
	{
		m_backGround.setTexture(&GameResources::getInstance().getHelpTexture(m_currentInstructionPage + 1), true);
		m_currentInstructionPage += 1;
	}
		

	if (m_direction == helpScreenCommand::BACKWARD && m_currentInstructionPage - 1 >= 0)
	{
		m_backGround.setTexture(&GameResources::getInstance().getHelpTexture(m_currentInstructionPage - 1), true);
		m_currentInstructionPage -= 1;
	}
		
}


