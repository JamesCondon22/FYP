#include "Headers/GameNode.h"

GameNode::GameNode(int size) {
	m_circle.setRadius(size);
}


GameNode::~GameNode()
{
}

void GameNode::setPosition(sf::Vector2f pos)
{
	m_position = pos;
	m_circle.setPosition(m_position);
}


void GameNode::setOrigin(int originX, int originY)
{
	m_circle.setOrigin(originX, originY);
}


int GameNode::getRadius()
{
	return m_circle.getRadius();
}


sf::Vector2f GameNode::getPosition() {
	return m_position;
}


void GameNode::setColor(sf::Color color)
{
	m_circle.setFillColor(color);
}


void GameNode::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_circle);
	}
}


