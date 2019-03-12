#include "../Include/Headers/DirectionalLine.h"


float const DirectionalLine::DEG_TO_RAD = 3.14 / 180.0f;
float const DirectionalLine::RAD_TO_DEG = 180.0f / 3.14;

DirectionalLine::DirectionalLine(sf::Vector2f one, double count, double points) :
	m_count(count),
	m_points(points)
{
	
	m_line[1] = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, points);

	m_mostDesired[0] = one;

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
	vec = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);

	m_line[1] = sf::Vector2f(vec.x, vec.y);
	m_map[m_current] = getPosition();

}

float DirectionalLine::mag(sf::Vector2f & v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

sf::Vector2f DirectionalLine::getVec(double x0, double y0, double r, double noOfDividingPoints, sf::Vector2f current)
{

	auto currentHighLevelVec = current;
	return sf::Vector2f();
	
}


void DirectionalLine::rotateLine(sf::Vector2f position, sf::Vector2f interestPosition, float direction, sf::Vector2f current)
{
	/*if (direction < 0)
	{
		RotateDirection = "LEFT";
	}
	else if (direction > 0)
	{
		RotateDirection = "RIGHT";
	}

	if (angle > 360)
	{
		angle = 0;
	}

	if (LastRotateDirection != RotateDirection)
	{
		angle = 0;
	}

	if (RotateDirection == "LEFT")
	{
		angle += 0.5;
	}
	else
	{
		angle -= 0.5;
	}*/

	//std::cout << getAngleBetween(interestPosition, current) << std::endl;
	

	if (current == vec)
	{
		std::cout << "ID " << m_count << std::endl;
	}
	m_mostDesired[0] = position;
	m_mostDesired[1] = interestPosition;

	m_line[0] = position;

	vec = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);

	auto rotatevec = vec - position;

	//thor::rotate(rotatevec, angle);

	vec = rotatevec + position;

	m_line[1] = sf::Vector2f(vec.x, vec.y);
	m_map[m_current] = getPosition();


	LastRotateDirection = RotateDirection;
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
	//window.draw(m_mostDesired, 2, sf::Lines);
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
}


sf::Vector2f DirectionalLine::getVector(int ind)
{
	std::map<Direction, sf::Vector2f>::iterator it;
	
	sf::Vector2f pos;

	for (it = m_map.begin(); it != m_map.end(); it++)
	{
		auto cur = static_cast<Direction>(ind);
		if (cur == it->first)
		{
			pos = it->second;
		}
	}

	return pos;
}


sf::Vector2f DirectionalLine::getAverage()
{
	return averagePosition;
}
