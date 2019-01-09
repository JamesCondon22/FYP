#include "Obstacle.h"



Obstacle::Obstacle(int size) :
	m_position(400,400)
{
	if (!m_texture.loadFromFile("obstacle.png")) {
		std::cout << "font not loaded" << std::endl;
	}
	m_circle.setTexture(&m_texture);
	m_circle.setRadius(size);
	m_circle.setOutlineColor(sf::Color::White);
	m_circle.setOutlineThickness(5);
	m_circle.setPosition(m_position);
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	
}

int Obstacle::getRadius()
{
	return m_circle.getRadius();
}

sf::Vector2f Obstacle::getPositon() {
	return m_position;
}

void Obstacle::render(sf::RenderWindow & window)
{
	window.draw(m_circle);
}
