#include "Headers/UI/GameNode.h"

GameNode::GameNode(float size, sf::Texture & texture) {
	m_radius = size;
	m_circle.setTexture(&texture);
	m_circle.setRadius(size);
}


GameNode::~GameNode()
{
}

/// <summary>
/// sets the node position to the pos vector 
/// </summary>
/// <param name="pos"></param>
void GameNode::setPosition(sf::Vector2f pos)
{
	m_position = pos;
	m_circle.setPosition(m_position);
}

/// <summary>
/// sets the origin of the node 
/// </summary>
/// <param name="originX">x origin</param>
/// <param name="originY">y origin</param>
void GameNode::setOrigin(int originX, int originY)
{
	m_circle.setOrigin(originX, originY);
}

/// <summary>
/// returns the radius of the node 
/// </summary>
/// <returns></returns>
int GameNode::getRadius()
{
	return m_circle.getRadius();
}

/// <summary>
/// returns the position of the node
/// </summary>
/// <returns></returns>
sf::Vector2f GameNode::getPosition() {
	return m_position;
}

/// <summary>
/// sets the color of the node 
/// </summary>
/// <param name="color">the color</param>
void GameNode::setColor(sf::Color color)
{
	m_circle.setFillColor(color);
}

/// <summary>
/// animates the node to expand and contract
/// </summary>
void GameNode::animateNode()
{
	if (animateOut)
	{
		m_radius += 0.05f;
		if (m_radius >= 15.0f)
		{
			animateOut = false;
			animateIn = true;
		}
	}
	if (animateIn)
	{
		m_radius -= 0.05f;
		if (m_radius <= 10.0f)
		{
			animateIn = false;
			animateOut = true;
		}
	}
	//updates the origin to the new origin 
	m_circle.setOrigin(m_radius / 2, m_radius / 2);
	m_circle.setRadius(m_radius);
}

/// <summary>
/// renders the node 
/// </summary>
/// <param name="window"></param>
void GameNode::render(sf::RenderWindow & window)
{
	if (m_alive)
	{
		window.draw(m_circle);
	}
}


