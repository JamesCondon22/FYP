#include "../Include/Headers/DirectionalLine.h"


float const DirectionalLine::DEG_TO_RAD = 3.14 / 180.0f;
float const DirectionalLine::RAD_TO_DEG = 180.0f / 3.14;

DirectionalLine::DirectionalLine(sf::Vector2f one, double count, double points) :
	m_count(count),
	m_points(points)
{
	m_line[0] = one;
	m_line[1] = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, points);
	assignDirection(m_count);
}

sf::Vector2f DirectionalLine::getPoints(double x0, double y0, double r, double noOfDividingPoints)
{
	sf::Vector2f pos;
	double angle = 0;

	angle = m_count * (360 / noOfDividingPoints);

	pos.x = (int)(x0 + r * cos(DEG_TO_RAD * angle));
	pos.y = (int)(y0 + r * sin(DEG_TO_RAD * angle));
	
	return pos;
}

sf::Vector2f DirectionalLine::getPosition() {
	return m_line[1].position;
}


DirectionalLine::~DirectionalLine()
{
}

void DirectionalLine::update(sf::Vector2f position)
{
	
	
	m_line[0] = position;
	sf::Vector2f vec = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);
	//thor::rotate(vec, 20.0f);
	m_line[1] = sf::Vector2f(vec.x, vec.y);
	m_map[m_current] = getPosition();
}

void DirectionalLine::setRadius(int rad)
{
	m_radius = rad;
}

std::map< Direction, sf::Vector2f> DirectionalLine::getMap() {
	return m_map;
}

Direction DirectionalLine::getState()
{
	return m_current;
}

void DirectionalLine::render(sf::RenderWindow & window)
{
	window.draw(m_line, 2, sf::Lines);
}

void DirectionalLine::changeColor() {
	m_line->color = sf::Color::Red;
}


void DirectionalLine::assignDirection(int count) {

	m_current = static_cast<Direction>(count);
	m_map.insert({ m_current, getPosition() });
}

void DirectionalLine::calculateAverage(std::vector<int> indices)
{
	averagePosition = sf::Vector2f(0, 0);

	std::map<Direction, sf::Vector2f>::iterator it;

	for (it = m_map.begin(); it != m_map.end(); it++)
	{
		for (int i = 0; i < indices.size(); i++)
		{
			auto cur = static_cast<Direction>(indices[i]);
			if (cur == it->first)
			{
				averagePosition += it->second;
			}
		}
	}

	averagePosition.x = averagePosition.x / indices.size();
	averagePosition.y = averagePosition.y / indices.size();
	std::cout << averagePosition.x << std::endl;
}

sf::Vector2f DirectionalLine::getAverage()
{
	return averagePosition;
}
