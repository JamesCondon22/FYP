#include "Traditional.h"


Traditional::Traditional() :
	m_steering(0,0),
	m_position(0, 0),
	m_heading(0,0),
	m_rotation(0),
	m_velocity(0, 0),
	m_relVelocity(0, 0),
	shape(100.0f),
	m_maxSpeed(1.0f),
	m_maxRotation(20.0f),
	m_timeToTarget(80.0f),
	m_maxTimePrediction(10.0f),
	m_relSpeed(0.0f),
	m_radius(75.0f),
	m_threshold(30.0f)
{
	//m_direction
	if (!m_texture.loadFromFile("enemy.png")) {
		std::cout << "font not loaded" << std::endl;
	}

	m_rect.setTexture(&m_texture);
	m_rect.setOrigin(m_position.x + 75 / 2, m_position.y + 50 / 2);
	m_rect.setSize(sf::Vector2f(75, 50));
	m_rect.setPosition(m_position);
	srand(time(NULL));

}

Traditional::~Traditional()
{

}
sf::Vector2f Traditional::getPosition()
{
	return m_rect.getPosition();
}
sf::Vector2f Traditional::getVelocity()
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
void Traditional::respawn(float x, float y)
{


	if (x > 2020)
	{
		m_position.x = -200;
		m_velocity.x = getRandom(10, 1);
		m_velocity.y = getRandom(21, -10);
	}
	if (x < -200)
	{
		m_position.x = 1920;
		m_velocity.x = getRandom(-10, -1);
		m_velocity.y = getRandom(21, -10);
	}
	if (y < -200)
	{
		m_position.y = 1080;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(-10, -1);
	}
	if (y > 1180)
	{
		m_position.y = -200;
		m_velocity.x = getRandom(21, -10);
		m_velocity.y = getRandom(10, 1);
	}

}

float Traditional::getRandom(int a, int b)
{
	srand(time(NULL));
	float randVal = rand() % a + b;
	return randVal;

}

void Traditional::kinematicArrive(sf::Vector2f playerPosition)
{
	//Get magnitude of vector
	m_velocityF = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	m_velocity = playerPosition - m_position;

	if (m_velocityF >= 0)
	{
		m_velocity = m_velocity / m_timeToTarget;

		if (m_velocityF > m_maxSpeed) {

			//Normalize vector
			m_velocity.x = m_velocity.x / m_velocityF;
			m_velocity.y = m_velocity.y / m_velocityF;

			m_velocity = m_velocity * m_maxSpeed;

		}

		//m_rotation = getNewOrientation(m_rotation, m_velocityF);
	}

}
sf::Vector2f Traditional::pursue(sf::Vector2f playerPosition, sf::Vector2f playerVelocity)
{
	m_direction = playerPosition - m_position;

	/*m_distance = std::sqrt(m_direction.x*m_direction.x + m_direction.y* m_direction.y);

	m_speed = std::sqrt(m_velocity.x*m_velocity.x + m_velocity.y* m_velocity.y);

	if (m_speed <= m_distance / m_maxTimePrediction) {
		m_timePrediction = m_maxTimePrediction;
	}
	else {
		m_timePrediction = m_distance / m_speed;
	}
	m_targetPos = playerPosition + playerVelocity * m_timePrediction;
	*/
	kinematicArrive(playerPosition);

	return(m_direction);
	

}
void Traditional::update(double dt, sf::Vector2f player, sf::Vector2f velocity, std::vector<sf::CircleShape> obstacles)
{
	
	//m_steering = sf::Vector2f(0.0, 0.0);
	m_steering += pursue(player,velocity);
	m_steering += ObstacleAvoidance(obstacles);
	
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

	m_speed = thor::length(m_velocity);
	//m_rect.setPosition(m_rect.getPosition().x + std::cos(DEG_TO_RAD  * m_rotation) * m_speed * (dt / 1000), m_rect.getPosition().y + std::cos(DEG_TO_RAD  * m_rotation)* m_speed * (dt / 1000));
	
	m_position += m_velocity;
	m_rect.setPosition(m_position);
	m_rect.setRotation(m_rotation);
	respawn(m_rect.getPosition().x, m_rect.getPosition().y);

}
sf::Vector2f Traditional::ObstacleAvoidance(std::vector<sf::CircleShape> obstacles) {
	
	
	//auto norm = thor::unitVector(m_velocity);
	auto headingRadians = thor::toRadian(m_rotation);
	auto dynamic = thor::length(m_velocity) / 10.0f;
	sf::Vector2f headingVector(cos(headingRadians) * dynamic, sin(headingRadians) * dynamic);
	
	ahead = m_position + thor::unitVector(m_velocity) + headingVector;
	ahead2 = m_position + thor::unitVector(m_velocity) + (headingVector * 0.5f);

	auto mostThreatening = findMostThreathening(obstacles);
	auto avoidance = sf::Vector2f(0, 0);
	if (mostThreatening.getRadius() != 0.0)
	{
		avoidance.x = ahead.x - mostThreatening.getPosition().x;
		avoidance.y = ahead.y - mostThreatening.getPosition().y;
		avoidance = thor::unitVector(avoidance);
		avoidance *= MAX_AVOID_FORCE;
	}
	else {
		avoidance *= 0.0f;
	}
	/*std::cout << avoidance.x << ", " << avoidance.y << std::endl;
	std::cout << mostThreatening.getRadius() << std::endl;*/
	return avoidance;
}


sf::CircleShape Traditional::findMostThreathening(std::vector<sf::CircleShape> obstacles)
{
	sf::CircleShape mostThreathening(0);
	for (int i = 0; i < obstacles.size(); i++) {
		sf::CircleShape obstacle = obstacles[i];
		bool collision = lineIntersectsCircle(ahead, ahead2, obstacle);

		if (collision && mostThreathening.getRadius() == 0.0 )
		{
			mostThreathening = obstacle;
		}
		//std::cout << collision << std::endl;
	
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
	auto dist = sqrt((pos.x - obst.x + 100) * (pos.x - obst.x + 100) + (pos.y - obst.y + 100)*(pos.y - obst.y + 100));
	std::cout << dist << std::endl;
	return dist;
}

bool Traditional::lineIntersectsCircle(sf::Vector2f vecOne, sf::Vector2f vecTwo, sf::CircleShape circle)
{
	//std::cout << m_distance << std::endl;
	return distance(circle.getPosition(), vecOne) <= circle.getRadius() || distance(circle.getPosition(), vecTwo) <= circle.getRadius();
}


void Traditional::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}