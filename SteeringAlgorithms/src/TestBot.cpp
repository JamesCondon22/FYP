#include "../Include/Headers/TestBot.h"


TestBot::TestBot(std::vector<GameNode*> path, std::vector<Obstacle*> obs) :
	m_steering(0, 0),
	m_position(0, 0),
	m_rotation(0),
	m_speed(1.5),
	m_velocity(1, 1),
	m_nodes(path),
	m_obstacles(obs)
{
	//m_direction
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
		lines[i].setOrigin(m_position.x - 25, m_position.y + 1);
	}
	m_position = sf::Vector2f(1600, 100);

	m_rect.setPosition(m_position);

	m_rect.setFillColor(sf::Color(220, 53, 44));
	m_rect.setOutlineColor(sf::Color::Black);

	srand(time(NULL));

	m_rotation = 180;
	m_rect.rotate(180);

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));
}


TestBot::~TestBot()
{

}


sf::Vector2f TestBot::getPosition()
{
	return m_rect.getPosition();
}


sf::Vector2f TestBot::getVelocity()
{
	return m_velocity;
}


float TestBot::getNewOrientation(float currentOrientation, float velocity)
{
	if (velocity >0)
	{
		return (std::atan2(-m_velocity.x, m_velocity.y) * 180.0 / 3.141592653589793238463);
	}
	else {
		return currentOrientation;
	}

}


float TestBot::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}


sf::Vector2f TestBot::seek()
{
	sf::Vector2f vecToNode;
	vecToNode = getCurrentNodePosition();

	m_direction = vecToNode - m_position;
	return(m_direction);
}


void TestBot::update(double dt)
{

	m_steering += seek();

	m_steering += ObstacleAvoidance();

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
		m_rotation = static_cast<int>((m_rotation)+1) % 360;
	}
	else
	{
		// rotate anti-clockwise
		m_rotation -= 1;
	}

	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);
	m_surroundingCircle.setPosition(m_position);

	for (int i = 0; i < lines.size(); i++) {
		lines[i].setPosition(m_position.x, m_position.y);
		lines[i].setRotation(m_rotation);
	}
}


sf::Vector2f TestBot::ObstacleAvoidance() {

	auto norm = thor::unitVector(m_velocity);
	auto headingRadians = thor::toRadian(m_rotation);
	auto dynamic = thor::length(m_velocity);
	
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


Obstacle* TestBot::findMostThreathening()
{
	Obstacle* mostThreathening = new Obstacle(0);
	for (int i = 0; i < m_obstacles.size(); i++) {
		Obstacle* obstacle = m_obstacles[i];
		bool collision = Math::lineIntersectsCircle(ahead, ahead2, obstacle);

		if (collision && mostThreathening->getRadius() == 0.0)
		{
			mostThreathening = obstacle;
		}

	}

	return mostThreathening;
}


sf::Vector2f TestBot::truncate(sf::Vector2f v, float const num)
{
	float i;
	i = num / thor::length(v);
	i = i < 1.0 ? i : 1.0;
	v *= i;
	return v;
}


sf::Vector2f TestBot::getCurrentNodePosition()
{

	sf::Vector2f target;

	target = m_nodes[currentNode]->getPosition();

	if (Math::distance(m_position, target) <= 150)
	{
		currentNode += 1;
		if (currentNode >= m_nodes.size()) {
			currentNode = 0;
		}
	}

	return target;
}


void TestBot::render(sf::RenderWindow & window)
{
	if (m_visuals) {
		window.draw(m_surroundingCircle);
		for (int i = 0; i < lines.size(); i++)
		{
			window.draw(lines[i]);
		}
	}
	window.draw(m_rect);

}


void TestBot::reset()
{
	m_position = sf::Vector2f(1600, 100);
	currentNode = 0;
	m_rotation = 180;
}