#include "Headers/Tile.h"



Tile::Tile(int x, int y, int dx, int dy) :
	m_position(x, y),
	posX(dx),
	posY(dy),
	m_gridPos(dx, dy)
	
{
	m_current = NState::Blank;

	m_rect.setSize(sf::Vector2f(30.0f, 30.0f));
	m_rect.setPosition(m_position);

	m_surround.setRadius(50);
	m_surround.setPosition(0, 0);
	m_surround.setFillColor(sf::Color(0, 0, 0, 157));
	m_surround.setOrigin(m_surround.getRadius(), m_surround.getRadius());
	m_surround.setPosition(m_position.x + 25, m_position.y + 25);

	m_interestPoint.setRadius(5);
	m_interestPoint.setPosition(0, 0);
	m_interestPoint.setFillColor(sf::Color(255, 0, 0));
	m_interestPoint.setOrigin(m_interestPoint.getRadius(), m_interestPoint.getRadius());
	m_interestPoint.setPosition(m_position.x + 25, m_position.y + 25);

	
}


Tile::~Tile()
{

}


void Tile::setObstacle()
{
	m_current = NState::Full;
}


void Tile::setCircularObs()
{
	m_current = NState::Circle;
}


void Tile::setKey() {

	m_current = NState::KeyObject;
}


void Tile::setBlank()
{
	m_current = NState::Blank;
}


void Tile::setInterest()
{
	m_current = NState::Interest;
}


NState Tile::getState()
{
	return m_current;
}


void Tile::render(sf::RenderWindow & window)
{	
	if (m_current == NState::Full)
	{
		//window.draw(m_surround);
	}
	window.draw(m_rect);

	switch (m_current)
	{
	case NState::Blank:
		m_rect.setFillColor(sf::Color::White);
		break;
	case NState::Full:
		m_rect.setFillColor(sf::Color::Black);
		break;
	case NState::Circle:
		//window.draw(m_CircleObs);
	default:
		break;
	}
	
}


void Tile::setColor(sf::Color col)
{

	m_rect.setFillColor(sf::Color(col));
}
