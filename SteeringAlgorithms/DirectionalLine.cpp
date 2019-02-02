#include "DirectionalLine.h"


double const DirectionalLine::DEG_TO_RAD = 3.14 / 180.0f;
double const DirectionalLine::RAD_TO_DEG = 180.0f / 3.14;

DirectionalLine::DirectionalLine(sf::Vector2f one, double count, double points) :
	m_count(count),
	m_points(points)
{
	m_line[0] = one;
	m_line[1] = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, points);
	assignDirection();
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
	m_line[1] = getPoints(m_line[0].position.x, m_line[0].position.y, m_radius, m_points);
	updatePositions();
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
	m_radius = 150;
}

void DirectionalLine::updatePositions()
{
	if (m_count == 0) { m_map[Direction::E] = getPosition(); };
	if (m_count == 1) { m_map[Direction::ESE] = getPosition(); };
	if (m_count == 2) { m_map[Direction::SE] = getPosition(); };
	if (m_count == 3) { m_map[Direction::SSE] = getPosition(); };
	if (m_count == 4) { m_map[Direction::S] = getPosition(); };
	if (m_count == 5) { m_map[Direction::SSW] = getPosition(); };
	if (m_count == 6) { m_map[Direction::SW] = getPosition(); };
	if (m_count == 7) { m_map[Direction::WSW] = getPosition(); };
	if (m_count == 8) { m_map[Direction::W] = getPosition(); };
	if (m_count == 9) { m_map[Direction::WNW] = getPosition(); };
	if (m_count == 10) { m_map[Direction::NW] = getPosition(); };
	if (m_count == 11) { m_map[Direction::NNW] = getPosition(); };
	if (m_count == 12) { m_map[Direction::N] = getPosition(); };
	if (m_count == 13) { m_map[Direction::NNE] = getPosition(); };
	if (m_count == 14) { m_map[Direction::NE] = getPosition(); };
	if (m_count == 15) { m_map[Direction::ENE] = getPosition(); };
}

void DirectionalLine::assignDirection() {

	if (m_count == 0) { m_map.insert({ Direction::E, getPosition() }); m_current = Direction::E; };
	if (m_count == 1) { m_map.insert({ Direction::ESE, getPosition() }); m_current = Direction::ESE;};
	if (m_count == 2) { m_map.insert({ Direction::SE, getPosition() }); m_current = Direction::SE; };
	if (m_count == 3) { m_map.insert({ Direction::SSE, getPosition() }); m_current = Direction::SSE;};
	if (m_count == 4) { m_map.insert({ Direction::S, getPosition() }); m_current = Direction::S; };
	if (m_count == 5) { m_map.insert({Direction::SSW, getPosition() }); m_current = Direction::SSW;};
	if (m_count == 6) { m_map.insert({ Direction::SW, getPosition() }); m_current = Direction::SW; };
	if (m_count == 7) { m_map.insert({ Direction::WSW, getPosition() }); m_current = Direction::WSW;};
	if (m_count == 8) { m_map.insert({ Direction::W, getPosition() }); m_current = Direction::W; };
	if (m_count == 9) { m_map.insert({ Direction::WNW, getPosition() }); m_current = Direction::WNW;};
	if (m_count == 10) { m_map.insert({ Direction::NW, getPosition() }); m_current = Direction::NW; };
	if (m_count == 11) { m_map.insert({ Direction::NNW, getPosition() }); m_current = Direction::NNW;};
	if (m_count == 12) { m_map.insert({ Direction::N, getPosition() }); m_current = Direction::N; };
	if (m_count == 13) { m_map.insert({ Direction::NNE, getPosition() }); m_current = Direction::NNE;};
	if (m_count == 14) { m_map.insert({ Direction::NE, getPosition() }); m_current = Direction::NE; };
	if (m_count == 15) { m_map.insert({ Direction::ENE, getPosition() }); m_current = Direction::ENE;};
	

}
