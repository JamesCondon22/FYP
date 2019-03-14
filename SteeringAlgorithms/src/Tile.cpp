#include "Headers/Tile.h"



Tile::Tile(int x, int y, int dx, int dy) :
	m_position(x, y),
	posX(dx),
	posY(dy),
	m_gridPos(dx, dy)
	
{
	m_current = NState::Blank;

	m_rect.setSize(sf::Vector2f(50.0f, 50.0f));
	m_rect.setPosition(m_position);
}


Tile::~Tile()
{

}


void Tile::setObstacle()
{
	m_current = NState::Full;
}


void Tile::setBlank()
{
	m_current = NState::Blank;
}


NState Tile::getState()
{
	return m_current;
}


void Tile::render(sf::RenderWindow & window)
{

	switch (m_current)
	{
	case NState::Blank:
		m_rect.setFillColor(sf::Color::White);
		break;
	case NState::Full:
		m_rect.setFillColor(sf::Color::Black);
		break;
	default:
		break;
	}
	window.draw(m_rect);

}


void Tile::setColor(sf::Color col)
{
	m_rect.setFillColor(sf::Color(col));
}
