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

	m_surroundingCircle.setRadius(75);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	m_distances.assign(8, 0.0);
}


FrayAI::~FrayAI()
{
}

void FrayAI::update(double dt, sf::Vector2f position)
{
	updateLines(position);
	normalize();
	mapDecisions.update(m_distances);
	mapDecisions.getStrongest();
	checkDirection();
	seek(position);

	m_position += m_velocity;
	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position);
	

	
}


void FrayAI::render(sf::RenderWindow & window)
{
	window.draw(m_surroundingCircle);
	window.draw(m_rect);

	window.draw(line, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
	window.draw(line3, 2, sf::Lines);
	window.draw(line4, 2, sf::Lines);
	window.draw(line5, 2, sf::Lines);
	window.draw(line6, 2, sf::Lines);
	window.draw(line7, 2, sf::Lines);
	window.draw(line8, 2, sf::Lines);
}


sf::Vector2f FrayAI::getPos()
{
	return m_position;
}

sf::Vector2f FrayAI::getVel()
{
	return m_velocity;
}

void FrayAI::updateLines(sf::Vector2f position)
{
	line[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line[1] = sf::Vector2f(m_surroundingCircle.getPosition().x, m_surroundingCircle.getPosition().y - 100);
	line2[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line2[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 75, m_surroundingCircle.getPosition().y - 75);
	line3[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line3[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 100, m_surroundingCircle.getPosition().y);
	line4[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line4[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 75, m_surroundingCircle.getPosition().y + 75);
	line5[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line5[1] = sf::Vector2f(m_surroundingCircle.getPosition().x, m_surroundingCircle.getPosition().y + 100);
	line6[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line6[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 75, m_surroundingCircle.getPosition().y + 75);
	line7[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line7[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 100, m_surroundingCircle.getPosition().y);
	line8[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line8[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 75, m_surroundingCircle.getPosition().y - 75);

	m_distances[0] = Math::distance(sf::Vector2f(line[1].position.x, line[1].position.y), position);
	m_distances[1] = Math::distance(sf::Vector2f(line2[1].position.x, line2[1].position.y), position);
	m_distances[2] = Math::distance(sf::Vector2f(line3[1].position.x, line3[1].position.y), position);
	m_distances[3] = Math::distance(sf::Vector2f(line4[1].position.x, line4[1].position.y), position);
	m_distances[4] = Math::distance(sf::Vector2f(line5[1].position.x, line5[1].position.y), position);
	m_distances[5] = Math::distance(sf::Vector2f(line6[1].position.x, line6[1].position.y), position);
	m_distances[6] = Math::distance(sf::Vector2f(line7[1].position.x, line7[1].position.y), position);
	m_distances[7] = Math::distance(sf::Vector2f(line8[1].position.x, line8[1].position.y), position);


}

double FrayAI::findLargest()
{
	double largest = 0;
	for (auto iter = m_distances.begin(); iter != m_distances.end(); ++iter)
	{
		if (*iter > largest)
		{
			largest = *iter;
		}
	}
	return largest;
}

void FrayAI::normalize()
{
	curLargest = findLargest();

	for (int i = 0; i < m_distances.size(); i++)
	{
		m_distances[i] = 1 - (m_distances[i] / curLargest);
	}
}

void FrayAI::seek(sf::Vector2f position)
{
	m_velocity = curDirection - m_position;
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * 0.5f;
	//m_rotation = getNewOrientation(m_rotation, m_velocity);
	//m_rect.setRotation(m_rotation);
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

void FrayAI::checkDirection()
{
	if (mapDecisions.getStrongest() == m_distances[0])
	{
		curDirection = sf::Vector2f(line[1].position.x, line[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[1])
	{
		curDirection = sf::Vector2f(line2[1].position.x, line2[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[2])
	{
		curDirection = sf::Vector2f(line3[1].position.x, line3[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[3])
	{
		curDirection = sf::Vector2f(line4[1].position.x, line4[1].position.y);
	}

	if (mapDecisions.getStrongest() == m_distances[4])
	{
		curDirection = sf::Vector2f(line5[1].position.x, line5[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[5])
	{
		curDirection = sf::Vector2f(line6[1].position.x, line6[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[6])
	{
		curDirection = sf::Vector2f(line7[1].position.x, line7[1].position.y);
	}
	if (mapDecisions.getStrongest() == m_distances[7])
	{
		curDirection = sf::Vector2f(line8[1].position.x, line8[1].position.y);
	}

}
