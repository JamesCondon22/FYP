#include "FrayAI.h"


double const FrayAI::DEG_TO_RAD = 3.14 / 180.0f;
FrayAI::FrayAI() :
	m_position(0, 0),
	m_velocity(0, 0),
	size(100),
	m_rotation(0),
	m_speed(0),
	MAX_SPEED(350)
{
	if (!m_texture.loadFromFile("frayAI.png")) {
		//do something
	}
	m_rect.setOrigin(m_position.x + 75 / 2, m_position.y + 50 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(75, 50));
	m_position = sf::Vector2f(1000, 500);
	m_rect.setPosition(m_position);
	mapDecisions = ContextDecisionMaker();


}


FrayAI::~FrayAI()
{
}

void FrayAI::update(double dt, sf::Vector2f position)
{
	sf::Vector2f curPosition = position - m_position;
	curPosition = normalize(curPosition);
	std::cout << curPosition.x << ", " << curPosition.y << std::endl;

	m_rect.setPosition(m_position);
	mapDecisions.update(curPosition);
}

void FrayAI::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}


sf::Vector2f FrayAI::getPos()
{
	return m_position;
}

sf::Vector2f FrayAI::getVel()
{
	return m_velocity;
}

sf::Vector2f FrayAI::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}