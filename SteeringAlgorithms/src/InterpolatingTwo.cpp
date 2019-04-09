#include "../Include/Headers/InterpolatingTwo.h"

double const InterpolatingTwo::RAD_TO_DEG = 180.0f / 3.14;
double const InterpolatingTwo::DEG_TO_RAD = 3.14 / 180.0f;
InterpolatingTwo::InterpolatingTwo(std::vector<GameNode*>  path, std::vector<Obstacle*>  obs) :
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
	m_position = sf::Vector2f(2700, 300);
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
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}
	m_color = sf::Color(255, 165, 0);
	m_rect.setFillColor(m_color);
	m_rotation = 90;
	m_rect.setRotation(m_rotation);
}


InterpolatingTwo::~InterpolatingTwo()
{
}


void InterpolatingTwo::setPosition(sf::Vector2f position) {
	m_position = position;
	m_rect.setPosition(m_position);
}


void InterpolatingTwo::update(double dt, sf::Vector2f position)
{
	m_lastRotation = m_rotation;

	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}

	if (*m_currentBehaviour == BehaviourState::ChaseNode) {

		updateLines(getCurrentNodePosition());
	}
	else {

		updateLines(position);
	}
	updateDangers();
	m_distances = normalize(m_distances);
	m_distancesDanger = normalizeDangers(m_distancesDanger);

	mapDecisions.update(m_distances, m_distancesDanger);
	checkDirection();

	m_steering = seek(position);
	m_position += m_steering.linear;
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
		m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed* (dt / 1000));

	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_position);
	
	if (m_state == GameState::Demo) {
		generatePath(dt);
	}
	handleTimer();

	m_tickCounter += 1;

	calculateRotations();
}


void InterpolatingTwo::calculateRotations() {

	auto currentRotation = m_rotation;

	auto diff = abs(currentRotation - m_lastRotation);

	m_totalRotations += diff;
}


void InterpolatingTwo::render(sf::RenderWindow & window)
{
	if (m_state == GameState::Demo) {
		for (int i = 0; i < m_pathLine.size(); i++)
		{
			m_pathLine[i]->render(window);
		}
	}
	if (m_visuals) {
		for (int i = 0; i < m_size; i++) {
			m_lineVec[i].render(window);
		}
		window.draw(m_surroundingCircle);
	}
	
	window.draw(m_rect);
	
}


sf::Vector2f InterpolatingTwo::getPos()
{
	return m_position;
}

sf::Vector2f InterpolatingTwo::getVel()
{
	return m_velocity;
}

void InterpolatingTwo::updateLines(sf::Vector2f position)
{
	int count = 0;
	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		m_distances[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), position);
		count++;
	}
}


void InterpolatingTwo::updateDangers()
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
			//checkdistance
		count++;
	}

}

double InterpolatingTwo::findLargest(std::map<Direction, double> vec)
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


std::map<Direction, double> InterpolatingTwo::normalize(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = 1 - (it->second / curLargest);

	}

	return vec;
}

std::map<Direction, double> InterpolatingTwo::normalizeDangers(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = it->second / curLargest;
		
	}

	return vec;
}



steering InterpolatingTwo::seek(sf::Vector2f position)
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


void InterpolatingTwo::calculation() {

	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewOrientation(m_rotation, m_velocity);
	}
}


float InterpolatingTwo::mag(sf::Vector2f & v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}


/// <summary>
/// 
/// </summary>
/// <param name="curOrientation"></param>
/// <param name="velocity"></param>
/// <returns></returns>
float InterpolatingTwo::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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


/// <summary>
/// 
/// </summary>
/// <param name="vel"></param>
/// <returns></returns>
float InterpolatingTwo::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}


bool InterpolatingTwo::compareKeys(std::map<Direction, sf::Vector2f> vec) {
	
	
	return false;
}


void InterpolatingTwo::checkDirection()
{
	auto tempDirection = curDirection;

	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		if (mapDecisions.getBlendedStrongest() == it->getState()) {
			m_prevDirection = it->getMap()[mapDecisions.getBlendedStrongest()];
			it->changeColor();
		}
	}

	curDirection = Math::lerp(tempDirection, m_prevDirection, 0.08);
}


void InterpolatingTwo::initVector()
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


sf::Vector2f InterpolatingTwo::getCurrentNodePosition()
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


sf::Vector2f InterpolatingTwo::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}


void InterpolatingTwo::generatePath(double dt)
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


void InterpolatingTwo::handleTimer()
{
	if (!m_startTimer)
	{
		m_clock.restart();
		m_startTimer = true;
	}
	m_currentTime = m_clock.getElapsedTime().asMilliseconds();
}


double InterpolatingTwo::getAverageExecTime()
{
	m_averageExecTime = m_currentTime / m_tickCounter;
	return m_averageExecTime;
}


double InterpolatingTwo::getTimeEfficiency()
{
	m_timeEfficiency = m_currentTime / m_tickCounter;
	return m_timeEfficiency;
}


void InterpolatingTwo::resetGame() {
	for (int i = 0; i < m_nodes.size(); i++) {

		m_nodes[i]->setAlive(true);
	}
}


void InterpolatingTwo::resetDemo() {

	m_lastPathCircle = nullptr;
	m_timeAmount = 0;
	m_pathLine.clear();
	m_rotation = 90;
	m_startTimer = false;
	m_currentTime = 0;
	m_tickCounter = 0;
	m_totalRotations = 0;
	m_rect.setRotation(m_rotation);
	m_surroundingCircle.setPosition(m_position);
	for (int i = 0; i < m_size; i++)
	{
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}
}