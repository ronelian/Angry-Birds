#include "State.h"

void State::soundButtonClicked(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::SOUND)), true);
	}
	else
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::MUTE)), true);
	}
}

void State::setSoundTexture(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
		button.setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::MUTE)), true);
	else
		button.setTexture(&GameResources::getInstance().getButtons(static_cast<int>(buttonType::SOUND)), true);
}
