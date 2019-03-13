#include "../Include/Headers/EfficiencyAI.h"

double const EfficiencyAI::RAD_TO_DEG = 180.0f / 3.14;
double const EfficiencyAI::DEG_TO_RAD = 3.14 / 180.0f;
EfficiencyAI::EfficiencyAI(std::vector<sf::CircleShape> & path, std::vector<Obstacle*>  obs) :
	m_position(0, 0),
	m_velocity(0, 0),
	size(100),
	m_rotation(0),
	m_speed(1.5f),
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

	m_rect.setFillColor(sf::Color::Green);
}


EfficiencyAI::~EfficiencyAI()
{
}


void EfficiencyAI::update(double dt, sf::Vector2f position)
{
	m_clock2.restart();
	m_timeSinceLast += dt;

	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}

	updateLines(position);
	updateDangers();
	m_distances = normalize(m_distances);
	m_distancesDanger = normalizeDangers(m_distancesDanger);

	if (!m_begin || m_timeSinceLast > 500)
	{
		mapDecisions.update(m_distances, m_distancesDanger);
		m_timeSinceLast = 0;
	}
	
	checkDirection(dt);


	m_steering = seek(position);
	m_position += m_steering.linear;
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed* (dt / 1000));
	
	m_rect.setPosition(m_position);

	m_surroundingCircle.setPosition(m_position);
	generatePath(dt);
	handleTimer();

	m_tickCounter += 1;
	m_time += m_clock2.getElapsedTime();

	m_begin = true;
}


void EfficiencyAI::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].render(window);
	}

	window.draw(m_surroundingCircle);
	window.draw(m_rect);
	
}


sf::Vector2f EfficiencyAI::getPos()
{
	return m_position;
}


sf::Vector2f EfficiencyAI::getVel()
{
	return m_velocity;
}


void EfficiencyAI::updateLines(sf::Vector2f position)
{
	sf::Vector2f vecToNode;
	vecToNode = getCurrentNodePosition();
	
	int count = 0;
	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		m_distances[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), position);
		count++;
	}
}


void EfficiencyAI::updateDangers()
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

	if (obs->getID() != m_prevId)
	{
		MaxDistance = smallest;
		std::cout << "ID = " << obs->getID() << std::endl;
		std::cout << MaxDistance << std::endl;
		WantedDistance = MaxDistance * .7;
		startTimer = true;
	}
	

	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		
		m_distancesDanger[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), obs->getPosition());
		count++;
	}
	m_prevId = obs->getID();
}


double EfficiencyAI::findLargest(std::map<Direction, double> vec)
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


std::map<Direction, double> EfficiencyAI::normalize(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = 1 - (it->second / curLargest);

	}

	return vec;
}


std::map<Direction, double> EfficiencyAI::normalizeDangers(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = it->second / curLargest;
		
	}

	return vec;
}


steering EfficiencyAI::seek(sf::Vector2f position)
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


void EfficiencyAI::calculation() {
	
	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewOrientation(m_rotation, m_velocity);
	}
}


float EfficiencyAI::mag(sf::Vector2f & v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}


float EfficiencyAI::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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


float EfficiencyAI::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}


void EfficiencyAI::checkDirection(double dt)
{

	sf::Vector2f temporaryDir = curDirection;

	auto current = mapDecisions.getAverage();
	auto average = sf::Vector2f(0, 0);

	for (int i = 0; i < current.size(); i++)
	{
		average += m_lineVec[current[i]].getPosition();
	}

	average.x = average.x / current.size();
	average.y = average.y / current.size();

	curDirection = Math::lerp(temporaryDir, average, 0.05);

}


void EfficiencyAI::initVector()
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


sf::Vector2f EfficiencyAI::getCurrentNodePosition()
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


sf::Vector2f EfficiencyAI::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}



void EfficiencyAI::generatePath(double dt)
{
	m_timeAmount += dt;

	if (m_timeAmount > 150)
	{
		Path * circle = new Path(3);
		circle->setPosition(m_position);
		m_pathLine.push_back(circle);
		m_timeAmount = 0;
		if (m_lastPathCircle != nullptr)
		{
			auto dist = Math::distance(m_lastPathCircle->getPosition(), circle->getPosition());
			m_totalPathLength += dist;
		}
		m_lastPathCircle = circle;
	}

	//std::cout << "Length = " << m_totalPathLength << std::endl;
}


void EfficiencyAI::handleTimer()
{
	m_currentTime += m_clock.restart().asMilliseconds();

	if (!m_startTimer)
	{
		m_currentTime -= m_currentTime;
		m_startTimer = true;
	}
}


double EfficiencyAI::getAverageExecTime()
{
	m_averageExecTime = (double)m_time.asMicroseconds() / m_tickCounter;
	return m_averageExecTime;
}


double EfficiencyAI::getTimeEfficiency()
{
	m_timeEfficiency = m_currentTime / m_tickCounter;
	return m_timeEfficiency;
}