#include "../Include/Headers/DirectionalLine.h"


float const DirectionalLine::DEG_TO_RAD = 3.14 / 180.0f;
float const DirectionalLine::RAD_TO_DEG = 180.0f / 3.14;

/// <summary>
/// initialises each vector
/// </summary>
/// <param name="one">starting point</param>
/// <param name="count">count of vectors</param>
/// <param name="points">no. of vectors</param>
DirectionalLine::DirectionalLine(sf::Vector2f one, double count, double points) :
	m_count(count),
	m_points(points)
{
	//sets position of line
	m_line[1] = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, points);

	m_mostDesired[0] = one;

	assignDirection(m_count);
}

/// <summary>
/// seperates the vectors around the entity
/// </summary>
/// <param name="x0">position x</param>
/// <param name="y0">position y</param>
/// <param name="r">radius</param>
/// <param name="noOfDividingPoints">no of points</param>
/// <returns></returns>
sf::Vector2f DirectionalLine::getPoints(double x0, double y0, double r, double noOfDividingPoints)
{
	sf::Vector2f pos;
	double angle = 0;

	angle = m_count * (360 / noOfDividingPoints);

	pos.x = (int)(x0 + r * cos(DEG_TO_RAD * angle));
	pos.y = (int)(y0 + r * sin(DEG_TO_RAD * angle));
	
	return pos;
}

/// <summary>
/// returns the position of the line
/// </summary>
/// <returns></returns>
sf::Vector2f DirectionalLine::getPosition() {
	return m_line[1].position;
}


DirectionalLine::~DirectionalLine()
{

}

/// <summary>
/// updates the position of the lines
/// </summary>
/// <param name="position"></param>
void DirectionalLine::update(sf::Vector2f position)
{
	m_line[0] = position;
	vec = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);

	m_line[1] = sf::Vector2f(vec.x, vec.y);
	m_map[m_current] = getPosition();

}

/// <summary>
/// rotates the vectors towards the desired position
/// updates the positions of the vectors
/// </summary>
/// <param name="position"></param>
/// <param name="interestPosition"></param>
/// <param name="direction"></param>
/// <param name="angleBtwn"></param>
void DirectionalLine::rotateLine(sf::Vector2f position, sf::Vector2f interestPosition, float direction, float angleBtwn)
{
	if (direction < 0) {
		RotateDirection = "LEFT";
	}
	else if (direction > 0) {
		RotateDirection = "RIGHT";
	}

	if (angle > 359) {
		angle = 0;
	}

	if (LastRotateDirection != RotateDirection) {
		
		angle = 0;
	}
	//sets the rotation whether left or right
	if (RotateDirection == "LEFT") {
		if (angleBtwn > 2)
		angle += 0.5;
	}
	else {
		if (angleBtwn > 2)
		angle -= 0.5;
	}
	//the position of the vector
	m_mostDesired[0] = position;
	m_mostDesired[1] = interestPosition;

	m_line[0] = position;
	//updates the position
	vec = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);

	auto rotatevec = vec - position;
	//rotates the vector by an angle
	thor::rotate(rotatevec, angle);

	vec = rotatevec + position;

	m_line[1] = sf::Vector2f(vec.x, vec.y);
	m_map[m_current] = getPosition();

	LastRotateDirection = RotateDirection;
}

/// <summary>
/// sets the radius 
/// </summary>
/// <param name="rad">radius</param>
void DirectionalLine::setRadius(int rad)
{
	m_radius = rad;
}

/// <summary>
/// returns a map of Directions and Vectors
/// </summary>
/// <returns>map</returns>
std::map< Direction, sf::Vector2f> DirectionalLine::getMap() {
	return m_map;
}

/// <summary>
/// returns the current State
/// </summary>
/// <returns>Direction </returns>
Direction DirectionalLine::getState()
{
	return m_current;
}

/// <summary>
/// render the lines 
/// </summary>
/// <param name="window"></param>
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

/// <summary>
/// calculates the average of the directions
/// to find a position 
/// </summary>
/// <param name="indices">directions</param>
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

/// <summary>
/// returns the vector of the Direction passed 
/// </summary>
/// <param name="ind"></param>
/// <returns></returns>
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

/// <summary>
/// returns the average
/// </summary>
/// <returns></returns>
sf::Vector2f DirectionalLine::getAverage()
{
	return averagePosition;
}
