#include "Obstacle.h"



Obstacle::Obstacle(int size) :
	m_position(400,400)
{
	if (!m_texture.loadFromFile("obstacle.png")) {
		std::cout << "font not loaded" << std::endl;
	}

	m_rectangle.setTexture(&m_texture);
	m_rectangle.setRadius(size);
	m_rectangle.setPosition(m_position);
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	
}

int Obstacle::getRadius()
{
	return m_rectangle.getRadius();
}

sf::Vector2f Obstacle::getPositon() {
	return m_position;
}

void Obstacle::render(sf::RenderWindow & window)
{
	window.draw(m_rectangle);
}
