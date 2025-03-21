#include "Window.h"

Window::Window() 
	: m_window{sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Angry Birds"}
{
	m_window.setFramerateLimit(60);
	resetView();
}


sf::RenderWindow& Window::getWindow() 
{
	return m_window;
}

void Window::setZoom(const float &zoom)
{
	auto view = m_window.getView();
	view.zoom(zoom);
	m_window.setView(view);
}

void Window::setView(const float& x, const float& y)
{
	auto view = m_window.getView();
	view.setCenter(x,y);
	m_window.setView(view);
}

void Window::resetView()
{
	m_window.setView(sf::View(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)));
}

