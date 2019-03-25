#include "Headers/GameNode.h"

GameNode::GameNode(float size, sf::Texture & texture) {
	m_radius = size;
	m_circle.setTexture(&texture);
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


void GameNode::animateNode()
{
	//m_circle.rotate(1);
	
	if (animateOut)
	{
		m_radius += 0.08f;
		if (m_radius >= 15.0f)
		{
			animateOut = false;
			animateIn = true;
		}
	}
	if (animateIn)
	{
		m_radius -= 0.08f;
		if (m_radius <= 10.0f)
		{
			animateIn = false;
			animateOut = true;
		}
	}

	m_circle.setRadius(m_radius);
}


void GameNode::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_circle);
	}
}


