#pragma once

#include "Macro.h"
#include <iostream>
#include <SFML/Graphics.hpp>




class Window
{
public:
	Window();
	~Window() = default;

	//getters
	sf::RenderWindow& getWindow();

	//setters
	void setZoom(const float& zoom);
	void setView(const float& x, const float& y);
	void resetView();

private:
	sf::RenderWindow m_window;

};

