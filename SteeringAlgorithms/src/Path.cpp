#include "Headers/Path.h"

Path::Path(int size)
{
	m_circle.setRadius(size);

}

Path::~Path()
{
	//deconstruct path
}


void Path::setPosition(sf::Vector2f pos)
{
	m_position = pos;
	m_circle.setPosition(m_position);
}


void Path::setOrigin(int originX, int originY)
{
	m_circle.setOrigin(originX, originY);
}


int Path::getRadius()
{
	return m_circle.getRadius();
}


sf::Vector2f Path::getPosition() {
	return m_position;
}


void Path::setColor(sf::Color color) {
	m_circle.setFillColor(color);
	m_circle.setOutlineThickness(1.0f);
	m_circle.setOutlineColor(sf::Color::Black);
}


void Path::setRadius(int rad)
{

}


void Path::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
}