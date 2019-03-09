#include "Headers/Path.h"

Path::Path(int size)
{
	m_circle.setRadius(size);
	m_circle.setFillColor(sf::Color::White);
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


void Path::setRadius(int rad)
{

}


void Path::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
}