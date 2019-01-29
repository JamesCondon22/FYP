#include "Obstacle.h"



Obstacle::Obstacle(int size) 
{
	if (!m_texture.loadFromFile("obstacle.png")) {
		std::cout << "font not loaded" << std::endl;
	}
	m_circle.setTexture(&m_texture);
	m_circle.setRadius(size);
	m_circle.setOutlineColor(sf::Color::White);
	m_circle.setOutlineThickness(5);
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	
}

void Obstacle::setPosition(sf::Vector2f pos)
{
	m_position = pos;
	m_circle.setPosition(m_position);
}


void Obstacle::setOrigin(int originX, int originY)
{
	m_circle.setOrigin(originX, originY);
}
int Obstacle::getRadius()
{
	return m_circle.getRadius();
}

sf::Vector2f Obstacle::getPosition() {
	return m_position;
}

void Obstacle::setRadius(int rad)
{

}
void Obstacle::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
}
