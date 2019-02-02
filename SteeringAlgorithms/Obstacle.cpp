#include "Obstacle.h"



Obstacle::Obstacle(int size, sf::Texture &texture) 
{
	m_circle.setTexture(&texture);
	m_circle.setRadius(size);

}
Obstacle::Obstacle(int size) {
	m_circle.setRadius(size);
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
