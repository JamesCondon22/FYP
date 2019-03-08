#include "../Include/Headers/DynamicVectorAI.h"

double const DynamicVectorAI::RAD_TO_DEG = 180.0f / 3.14;
double const DynamicVectorAI::DEG_TO_RAD = 3.14 / 180.0f;
DynamicVectorAI::DynamicVectorAI(std::vector<sf::CircleShape> & path, std::vector<Obstacle*>  obs) :
	m_position(0, 0),
	m_velocity(0, 0),
	size(100),
	m_rotation(0),
	m_speed(1.5),
	MAX_SPEED(100),
	m_nodes(path),
	m_obstacles(obs)
{
	if (!m_texture.loadFromFile("resources/assets/enemyTwo.png")) {
		//do something
	}
	m_rect.setOrigin(m_position.x + 25 / 2, m_position.y + 50 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(25, 50));
	m_position = sf::Vector2f(1800, 500);
	m_rect.setPosition(m_position);
	mapDecisions = ContextDecisionMaker();

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));


	initVector();
	
	for (int i = 0; i < m_size; i++)
	{
		DirectionalLine line = DirectionalLine(m_surroundingCircle.getPosition(), i, m_size);
		m_lineVec.push_back(line);
	}

	m_rect.setFillColor(sf::Color::Magenta);
}


DynamicVectorAI::~DynamicVectorAI()
{

}


void DynamicVectorAI::update(double dt, sf::Vector2f position)
{
	//m_rect.rotate(270);

	auto current = AngleDir(getCurrentNodePosition(), curDirection);

	for (int i = 0; i < m_size; i++) {

		m_lineVec[i].rotateLine(m_surroundingCircle.getPosition(), getCurrentNodePosition(), current, curDirection);
	}

	//std::cout << "DOT = " << current << std::endl;
	std::cout << "Angle Between = " << getAngleBetween(curDirection, getCurrentNodePosition()) << std::endl;

	updateLines(position);
	updateDangers();
	m_distances = normalize(m_distances);
	m_distancesDanger = normalizeDangers(m_distancesDanger);
	mapDecisions.update(m_distances, m_distancesDanger);
	checkDirection(dt);
	
	m_steering = seek(position);
	m_position += m_steering.linear;
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed * (dt / 1000));

	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_position);
}


/// <summary>
/// This function returns a negative number if B is to the left of A
/// Returns a positive if B is to the right os A
/// </summary>
/// <param name="A">The desired vector</param>
/// <param name="B">The current Direction vector</param>
/// <returns></returns>
float DynamicVectorAI::AngleDir(sf::Vector2f A, sf::Vector2f B)
{
	return -A.x * B.y + A.y * B.x;
}



float DynamicVectorAI::getAngleBetween(sf::Vector2f posOne, sf::Vector2f posTwo)
{

	auto dist = Math::distance(m_surroundingCircle.getPosition(), getCurrentNodePosition());
	auto ans = acos(40 / dist);
	return ans;
}


void DynamicVectorAI::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].render(window);
	}

	window.draw(m_surroundingCircle);
	window.draw(m_rect);
}


sf::Vector2f DynamicVectorAI::getPos()
{
	return m_position;
}


sf::Vector2f DynamicVectorAI::getVel()
{
	return m_velocity;
}


void DynamicVectorAI::updateLines(sf::Vector2f position)
{
	sf::Vector2f vecToNode;
	vecToNode = getCurrentNodePosition();
	
	int count = 0;
	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		m_distances[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), vecToNode);
		count++;
	}
}


void DynamicVectorAI::updateDangers()
{
	int count = 0;

	Obstacle *obs = new Obstacle(0);
	
	double smallest = 1000000;
	for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		double dist = Math::distance(m_position, (*it)->getPosition());
		if (dist < smallest)
		{
			obs = (*it);
			smallest = dist;
		}
	}

	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		
		m_distancesDanger[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), obs->getPosition());
		count++;
	}
}


double DynamicVectorAI::findLargest(std::map<Direction, double> vec)
{
	double largest = 0;
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		if (it->second > largest) {
			largest = it->second;
		}

	}
	return largest;
}


std::map<Direction, double> DynamicVectorAI::normalize(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);
	
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = 1 - (it->second / curLargest);

	}

	return vec;
}


std::map<Direction, double> DynamicVectorAI::normalizeDangers(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = it->second / curLargest;
		
	}

	return vec;
}


steering DynamicVectorAI::seek(sf::Vector2f position)
{
	m_velocity = curDirection - m_position;
	calculation();
	m_velocity = normalize(m_velocity);
	m_rect.setRotation(m_rotation);

	steering seekSteering;
	seekSteering.linear = m_velocity;
	seekSteering.angular = 0.0;
	return seekSteering;
}


void DynamicVectorAI::calculation() {
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewOrientation(m_rotation, m_velocity);
	}
}


float DynamicVectorAI::mag(sf::Vector2f & v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}


float DynamicVectorAI::getNewOrientation(float curOrientation, sf::Vector2f velocity)
{
	if (length(velocity) > 0)
	{
		float rotation = atan2(-velocity.x, velocity.y) * RAD_TO_DEG;
		return rotation;
	}
	else
	{
		return curOrientation;
	}
}


float DynamicVectorAI::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}


void DynamicVectorAI::checkDirection(double dt)
{

	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		if (mapDecisions.getStrongest() == it->getState()) {
			curDirection = it->getMap()[mapDecisions.getStrongest()];
			it->changeColor();
		}
	}

}


void DynamicVectorAI::initVector()
{
	
	m_distances.insert({ Direction::E, 0.0 });
	m_distances.insert({ Direction::ESE, 0.0 });
	m_distances.insert({ Direction::SE, 0.0 });
	m_distances.insert({ Direction::SSE, 0.0 });
	m_distances.insert({ Direction::S ,0.0 });
	m_distances.insert({ Direction::SSW, 0.0 });
	m_distances.insert({ Direction::SW, 0.0 });
	m_distances.insert({ Direction::WSW, 0.0 });
	m_distances.insert({ Direction::W, 0.0 });
	m_distances.insert({ Direction::WNW, 0.0 });
	m_distances.insert({ Direction::NW, 0.0 });
	m_distances.insert({ Direction::NNW, 0.0 });
	m_distances.insert({ Direction::N, 0.0 });
	m_distances.insert({ Direction::NNE, 0.0 });
	m_distances.insert({ Direction::NE, 0.0 });
	m_distances.insert({ Direction::ENE, 0.0 });

	
	m_distancesDanger.insert({ Direction::E, 0.0 });
	m_distancesDanger.insert({ Direction::ESE, 0.0 });
	m_distancesDanger.insert({ Direction::SE, 0.0 });
	m_distancesDanger.insert({ Direction::SSE, 0.0 });
	m_distancesDanger.insert({ Direction::S ,0.0 });
	m_distancesDanger.insert({ Direction::SSW, 0.0 });
	m_distancesDanger.insert({ Direction::SW, 0.0 });
	m_distancesDanger.insert({ Direction::WSW, 0.0 });
	m_distancesDanger.insert({ Direction::W, 0.0 });
	m_distancesDanger.insert({ Direction::WNW, 0.0 });
	m_distancesDanger.insert({ Direction::NW, 0.0 });
	m_distancesDanger.insert({ Direction::NNW, 0.0 });
	m_distancesDanger.insert({ Direction::N, 0.0 });
	m_distancesDanger.insert({ Direction::NNE, 0.0 });
	m_distancesDanger.insert({ Direction::NE, 0.0 });
	m_distancesDanger.insert({ Direction::ENE, 0.0 });
}


sf::Vector2f DynamicVectorAI::getCurrentNodePosition()
{
	
	sf::Vector2f target;

	target = m_nodes[currentNode].getPosition();

	if (Math::distance(m_position, target) <= 80)
	{
		currentNode += 1;
		if (currentNode >= m_nodes.size()) {
			currentNode = 0;
		}
	}

	return target;
}


sf::Vector2f DynamicVectorAI::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}