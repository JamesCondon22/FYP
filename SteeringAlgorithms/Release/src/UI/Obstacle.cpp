#include "../Include/Headers/UI/Obstacle.h"



Obstacle::Obstacle(int size, sf::Texture &texture, sf::Vector2f vec, bool isCir) :
	m_isCircle(isCir)
{
	if (m_isCircle) {
		m_circle.setTexture(&texture);
		m_circle.setRadius(size);
	}
	else {
		m_rect.setSize(vec);
	}
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

	if (m_isCircle) {
		m_circle.setPosition(m_position);
	}
	else {
		m_rect.setPosition(pos);
	}
}


void Obstacle::setOrigin(int originX, int originY)
{
	if (m_isCircle) {
		m_circle.setOrigin(originX, originY);
	}
	else {
		m_rect.setOrigin(originX, originY);
	}
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
	if (m_isCircle) {
		window.draw(m_circle);
	}
	else {
		window.draw(m_rect);
	}
	
}


void Obstacle::setColor(sf::Color color)
{
	if (m_isCircle) {
		m_circle.setFillColor(color);
	}
	else {
		m_rect.setFillColor(color);
	}
}
