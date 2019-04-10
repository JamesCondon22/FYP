#include "../Include/Headers/Traditional.h"


Traditional::Traditional(std::vector<GameNode*> node, std::vector<Obstacle*> obs) :
	m_steering(0, 0),
	m_position(0, 0),
	m_heading(0, 0),
	m_rotation(0),
	m_speed(1.05f),
	m_velocity(0, 0),
	m_nodes(node),
	m_obstacles(obs)
{
	if (!m_texture.loadFromFile("resources/assets/triangleOne.png")) {
		std::cout << "font not loaded" << std::endl;
	}

	m_rect.setTexture(&m_texture);

	m_rect.setSize(sf::Vector2f(50, 25));

	sf::RectangleShape line(sf::Vector2f(110, 3));
	sf::RectangleShape line2(sf::Vector2f(55, 3));

	line2.setFillColor(sf::Color::Red);
	m_rect.setOrigin(m_position.x + 50 / 2, m_position.y + 25 / 2);

	lines.push_back(line);
	lines.push_back(line2);

	for (int i = 0; i < lines.size(); i++) {
		lines[i].setOrigin(m_position.x - 25.0f, m_position.y + 1.0f);
	}
	m_position = sf::Vector2f(2700, 300);

	m_rect.setPosition(m_position);
	
	m_color = sf::Color(sf::Color(220, 53, 44));
	m_rect.setFillColor(m_color);
	m_rect.setOutlineColor(sf::Color::Black);

	m_rotation = 180.0f;
	m_rect.rotate(m_rotation);

	for (int i = 0; i < lines.size(); i++) {
		lines[i].setPosition(m_position);
		lines[i].setRotation(180.0f);
	}
	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

}


Traditional::~Traditional()
{

}


sf::Vector2f Traditional::getPos()
{
	return m_rect.getPosition();
}


sf::Vector2f Traditional::getVel()
{
	return m_velocity;
}


float Traditional::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}


void Traditional::setPosition(sf::Vector2f position) {
	m_position = position;
	m_rect.setPosition(m_position);
}


sf::Vector2f Traditional::pursue(sf::Vector2f position)
{
	sf::Vector2f vecToNode;
	vecToNode = position;

	m_direction = vecToNode - m_position;
	return(m_direction);
}


void Traditional::update(double dt, sf::Vector2f player)
{

	m_lastRotation = m_rotation;

	if (*m_currentBehaviour == BehaviourState::ChaseNode) {

		m_steering += pursue(getCurrentNodePosition());
	}
	else {

		m_steering += pursue(player);
	}
	
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		m_steering += ObstacleAvoidance();
	}
	
	m_steering = truncate(m_steering, MAX_FORCE);
	m_velocity = truncate(m_velocity + m_steering, MAX_SPEED);
	
	auto dest = atan2(-1 * m_velocity.y, -1 * m_velocity.x) / thor::Pi * 180 + 180;

	auto currentRotation = m_rotation;

	// Find the shortest way to rotate towards the player (clockwise or anti-clockwise)
	if (std::round(currentRotation - dest) == 0.0)
	{
		m_steering.x = 0;
		m_steering.y = 0;
	}
	else if ((static_cast<int>(std::round(dest - currentRotation + 360))) % 360 < 180)
	{
		// rotate clockwise
		m_rotation = static_cast<int>((m_rotation) + 1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation -= 1;
	}

	m_position += m_velocity;
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed* (dt / 1000));
	m_rect.setPosition(m_position);
	m_rect.setRotation(currentRotation);
	m_surroundingCircle.setPosition(m_position);
	for (int i = 0; i < lines.size(); i++) {
		lines[i].setPosition(m_position);
		lines[i].setRotation(m_rotation);
	}

	if (m_state == GameState::Demo) {

		generatePath(dt);
		handleTimer();
		m_tickCounter += 1;
		calculateRotations();
	}
}


void Traditional::calculateRotations() {

	auto currentRotation = m_rotation;

	auto diff = abs(currentRotation - m_lastRotation);

	m_totalRotations += diff;

}


double Traditional::getAverageRotations() {
	return m_totalRotations / m_currentTime;
}


sf::Vector2f Traditional::ObstacleAvoidance() {
	
	
	auto norm = thor::unitVector(m_velocity);
	auto headingRadians = thor::toRadian(m_rotation);
	auto dynamic = thor::length(m_velocity) / 10.0f;
	
	
	sf::Vector2f headingVector(cos(headingRadians) * dynamic, sin(headingRadians) * dynamic);
	
	ahead = m_position + norm + headingVector;
	ahead2 = m_position + norm + (headingVector * 0.5f);

	auto mostThreatening = findMostThreathening();
	auto avoidance = sf::Vector2f(0, 0);

	if (mostThreatening->getRadius() != 0.0)
	{
		avoidance.x = ahead.x - mostThreatening->getPosition().x;
		avoidance.y = ahead.y - mostThreatening->getPosition().y;
		avoidance = thor::unitVector(avoidance);
		avoidance *= MAX_AVOID_FORCE;
	}
	else {
		avoidance *= 0.0f;
	}
	
	return avoidance;
}


Obstacle* Traditional::findMostThreathening()
{
	Obstacle* mostThreathening = new Obstacle(0);
	for (int i = 0; i < m_obstacles.size(); i++) {
		Obstacle* obstacle = m_obstacles[i];
		bool collision = lineIntersectsCircle(ahead, ahead2, obstacle);

		if (collision && mostThreathening->getRadius() == 0.0 )
		{
			mostThreathening = obstacle;
		}
	
	}
	
	return mostThreathening;
}


sf::Vector2f Traditional::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}


sf::Vector2f Traditional::truncate(sf::Vector2f v, float const num)
{
	float i;
	i = num / thor::length(v);
	i = i < 1.0 ? i : 1.0;
	v *= i;
	return v;
}


sf::Vector2f Traditional::scale(sf::Vector2f vec, double val)
{
	vec.x = vec.x * val;
	vec.y = vec.y * val;

	return vec;
}


float Traditional::distance(sf::Vector2f pos, sf::Vector2f obst)
{
	auto dist = sqrt((pos.x - obst.x) * (pos.x - obst.x) + (pos.y - obst.y)*(pos.y - obst.y));
	return dist;
}


bool Traditional::lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, Obstacle* circle)
{
	return distance(circle->getPosition(), vecOne) <= circle->getRadius() || distance(circle->getPosition(), vecTwo) <= circle->getRadius();
}


sf::Vector2f Traditional::getCurrentNodePosition()
{

	sf::Vector2f target;

	double smallest = DBL_MAX;
	auto curIndex = 0;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->getAlive()) {
			auto dist = Math::distance(m_position, m_nodes[i]->getPosition());

			if (dist < smallest) {
				smallest = dist;
				target = m_nodes[i]->getPosition();
				curIndex = i;
			}
		}
	}
	m_nodeIndex = curIndex;
	return target;
}

/// <summary>
/// generates a path or trail which is left 
/// by the ai, updates the path using the dt value 
/// pushes the path into the a vector contaning the path nodes 
/// </summary>
/// <param name="dt">delta time</param>
void Traditional::generatePath(double dt)
{
	m_timeAmount += dt;

	if (m_timeAmount > 150)
	{
		Path * circle = new Path(3);
		circle->setPosition(m_position);
		circle->setColor(m_color);
		m_pathLine.push_back(circle);
		m_timeAmount = 0;
		if (m_lastPathCircle != nullptr)
		{
			auto dist = Math::distance(m_lastPathCircle->getPosition(), circle->getPosition());
			m_totalPathLength += dist;
		}
		m_lastPathCircle = circle;
	}
}

/// <summary>
/// updates the timer 
/// </summary>
void Traditional::handleTimer()
{
	if (!m_startTimer)
	{
		m_clock.restart();
		m_startTimer = true;
	}
	m_currentTime = m_clock.getElapsedTime().asMilliseconds();
	m_currentTime = m_currentTime / 1000;
}

/// <summary>
/// gets the average execution time 
/// calculates by dividing the time into the amount of ticks 
/// </summary>
/// <returns>average execution time</returns>
double Traditional::getAverageExecTime()
{
	m_averageExecTime = (m_currentTime * 1000) / m_tickCounter;
	return m_averageExecTime;
}


void Traditional::resetGame() {
	for (int i = 0; i < m_nodes.size(); i++) {

		m_nodes[i]->setAlive(true);
	}
}


void Traditional::resetDemo() {

	m_lastPathCircle = nullptr;
	m_totalPathLength = 0;
	m_timeAmount = 0;
	m_startTimer = false;
	m_currentTime = 0;
	m_tickCounter = 0;
	m_pathLine.clear();
	m_velocity= sf::Vector2f(0, 0),
	m_rotation = 180.0f;
	m_totalRotations = 0;
	m_surroundingCircle.setPosition(m_position);
	m_rect.setRotation(m_rotation);
	for (int i = 0; i < lines.size(); i++) {
		lines[i].setPosition(m_position);
		lines[i].setRotation(180.0f);
	}
}


void Traditional::render(sf::RenderWindow & window)
{

	if (m_state == GameState::Demo) {
		for (int i = 0; i < m_pathLine.size(); i++)
		{
			m_pathLine[i]->render(window);
		}
	}
	if (m_visuals) {
		for (int i = 0; i < lines.size(); i++)
		{
			window.draw(lines[i]);
		}
		window.draw(m_surroundingCircle);
	}
	window.draw(m_rect);
	
}