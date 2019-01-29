#include "FrayAI.h"

double const FrayAI::RAD_TO_DEG = 180.0f / 3.14;
double const FrayAI::DEG_TO_RAD = 3.14 / 180.0f;
FrayAI::FrayAI(std::vector<sf::CircleShape> & path) :
	m_position(0, 0),
	m_velocity(0, 0),
	size(100),
	m_rotation(0),
	m_speed(0),
	MAX_SPEED(100),
	m_nodes(path)
{
	if (!m_texture.loadFromFile("frayAI.png")) {
		//do something
	}
	m_rect.setOrigin(m_position.x + 50 / 2, m_position.y + 75 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(50, 75));
	m_position = sf::Vector2f(1500, 500);
	m_rect.setPosition(m_position);
	mapDecisions = ContextDecisionMaker();

	m_surroundingCircle.setRadius(m_radius);
	m_surroundingCircle.setPosition(0, 0);
	m_surroundingCircle.setOrigin(m_surroundingCircle.getRadius(), m_surroundingCircle.getRadius());
	m_surroundingCircle.setPosition(m_position);
	m_surroundingCircle.setFillColor(sf::Color(0, 0, 0, 40));

	
	initVector();
	
}


FrayAI::~FrayAI()
{
}

void FrayAI::update(double dt, sf::Vector2f position, Obstacle* obstacles)
{
	updateLines(position);
	updateDangers(obstacles);
	m_distances = normalize(m_distances);
	m_distancesDanger = normalizeDangers(m_distancesDanger);
	mapDecisions.update(m_distances, m_distancesDanger);
	checkDirection();
	seek(position);

	m_position += m_velocity;
	m_surroundingCircle.setPosition(m_position);
	m_rect.setPosition(m_position);
	

	
}


void FrayAI::render(sf::RenderWindow & window)
{
	window.draw(m_surroundingCircle);
	window.draw(m_rect);

	window.draw(line, 2, sf::Lines);
	window.draw(line2, 2, sf::Lines);
	window.draw(line3, 2, sf::Lines);
	window.draw(line4, 2, sf::Lines);
	window.draw(line5, 2, sf::Lines);
	window.draw(line6, 2, sf::Lines);
	window.draw(line7, 2, sf::Lines);
	window.draw(line8, 2, sf::Lines);
}


sf::Vector2f FrayAI::getPos()
{
	return m_position;
}

sf::Vector2f FrayAI::getVel()
{
	return m_velocity;
}

void FrayAI::updateLines(sf::Vector2f position)
{
	line[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line[1] = sf::Vector2f(m_surroundingCircle.getPosition().x , m_surroundingCircle.getPosition().y - 75);
	line2[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line2[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 50, m_surroundingCircle.getPosition().y - 50);
	line3[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line3[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 75, m_surroundingCircle.getPosition().y);
	line4[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line4[1] = sf::Vector2f(m_surroundingCircle.getPosition().x + 50, m_surroundingCircle.getPosition().y + 50);
	line5[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line5[1] = sf::Vector2f(m_surroundingCircle.getPosition().x, m_surroundingCircle.getPosition().y + 75);
	line6[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line6[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 50, m_surroundingCircle.getPosition().y + 50);
	line7[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line7[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 75, m_surroundingCircle.getPosition().y);
	line8[0] = sf::Vector2f(m_surroundingCircle.getPosition());
	line8[1] = sf::Vector2f(m_surroundingCircle.getPosition().x - 50, m_surroundingCircle.getPosition().y - 50);

	sf::Vector2f vecToNode;
	vecToNode = getCurrentNodePosition();
	
	m_distances[0].first = Math::distance(sf::Vector2f(line[1].position.x, line[1].position.y), vecToNode);
	m_distances[1].first = Math::distance(sf::Vector2f(line2[1].position.x, line2[1].position.y), vecToNode);
	m_distances[2].first = Math::distance(sf::Vector2f(line3[1].position.x, line3[1].position.y), vecToNode);
	m_distances[3].first = Math::distance(sf::Vector2f(line4[1].position.x, line4[1].position.y), vecToNode);
	m_distances[4].first = Math::distance(sf::Vector2f(line5[1].position.x, line5[1].position.y), vecToNode);
	m_distances[5].first = Math::distance(sf::Vector2f(line6[1].position.x, line6[1].position.y), vecToNode);
	m_distances[6].first = Math::distance(sf::Vector2f(line7[1].position.x, line7[1].position.y), vecToNode);
	m_distances[7].first = Math::distance(sf::Vector2f(line8[1].position.x, line8[1].position.y), vecToNode);


}

void FrayAI::updateDangers(Obstacle* obstacles)
{
	
		m_distancesDanger[0].first = Math::distance(sf::Vector2f(line[1].position.x, line[1].position.y), obstacles->getPosition());
		m_distancesDanger[1].first = Math::distance(sf::Vector2f(line2[1].position.x, line2[1].position.y), obstacles->getPosition());
		m_distancesDanger[2].first = Math::distance(sf::Vector2f(line3[1].position.x, line3[1].position.y), obstacles->getPosition());
		m_distancesDanger[3].first = Math::distance(sf::Vector2f(line4[1].position.x, line4[1].position.y), obstacles->getPosition());
		m_distancesDanger[4].first = Math::distance(sf::Vector2f(line5[1].position.x, line5[1].position.y), obstacles->getPosition());
		m_distancesDanger[5].first = Math::distance(sf::Vector2f(line6[1].position.x, line6[1].position.y), obstacles->getPosition());
		m_distancesDanger[6].first = Math::distance(sf::Vector2f(line7[1].position.x, line7[1].position.y), obstacles->getPosition());
		m_distancesDanger[7].first = Math::distance(sf::Vector2f(line8[1].position.x, line8[1].position.y), obstacles->getPosition());
	
	
}

std::pair<double, std::string > FrayAI::findLargest(std::vector<std::pair<double, std::string>> vec)
{
	std::sort(vec.begin(), vec.end());
	return vec.at(vec.size()-1);

	
}

std::vector<std::pair<double, std::string>> FrayAI::normalize(std::vector<std::pair<double, std::string>> vec)
{
	auto curLargest = findLargest(vec);

	for (int i = 0; i < vec.size(); i++)
	{
		vec[i].first = 1 - (vec[i].first / curLargest.first);
	}
	return vec;
}

std::vector<std::pair<double, std::string>> FrayAI::normalizeDangers(std::vector<std::pair<double, std::string>> vec)
{
	auto curLargest = findLargest(vec);

	for (int i = 0; i < vec.size(); i++)
	{
		vec[i].first = (vec[i].first / curLargest.first);
	}
	return vec;
}



void FrayAI::seek(sf::Vector2f position)
{
	m_velocity = curDirection - m_position;
	m_velocity = normalize(m_velocity);
	m_velocity = m_velocity * 0.3f;
	m_rotation = getNewOrientation(m_rotation, m_velocity);
	m_rect.setRotation(m_rotation);
}

/// <summary>
/// 
/// </summary>
/// <param name="curOrientation"></param>
/// <param name="velocity"></param>
/// <returns></returns>
float FrayAI::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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
float FrayAI::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

sf::Vector2f FrayAI::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}

void FrayAI::checkDirection()
{
	
	if (mapDecisions.getStrongest().second == "UP")
	{
		curDirection = sf::Vector2f(line[1].position.x, line[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "UPRIGHT")
	{
		curDirection = sf::Vector2f(line2[1].position.x, line2[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "RIGHT")
	{
		curDirection = sf::Vector2f(line3[1].position.x, line3[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "DOWNRIGHT")
	{
		curDirection = sf::Vector2f(line4[1].position.x, line4[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "DOWN")
	{
		curDirection = sf::Vector2f(line5[1].position.x, line5[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "DOWNLEFT")
	{
		curDirection = sf::Vector2f(line6[1].position.x, line6[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "LEFT")
	{
		curDirection = sf::Vector2f(line7[1].position.x, line7[1].position.y);
	}
	if (mapDecisions.getStrongest().second == "UPLEFT")
	{
		curDirection = sf::Vector2f(line8[1].position.x, line8[1].position.y);
	}
	//std::cout << mapDecisions.getStrongest().second << std::endl;
}

void FrayAI::initVector()
{
	m_distances.assign(8, std::make_pair(0.0, "NONE"));
	m_distancesDanger.assign(8, std::make_pair(0.0, "NONE"));
	m_distances[0] = std::make_pair(0.0, "UP");
	m_distances[1] = std::make_pair(0.0, "UPRIGHT");
	m_distances[2] = std::make_pair(0.0, "RIGHT");
	m_distances[3] = std::make_pair(0.0, "DOWNRIGHT");
	m_distances[4] = std::make_pair(0.0, "DOWN");
	m_distances[5] = std::make_pair(0.0, "DOWNLEFT");
	m_distances[6] = std::make_pair(0.0, "LEFT");
	m_distances[7] = std::make_pair(0.0, "UPLEFT");

	m_distancesDanger[0] = std::make_pair(0.0, "UP");
	m_distancesDanger[1] = std::make_pair(0.0, "UPRIGHT");
	m_distancesDanger[2] = std::make_pair(0.0, "RIGHT");
	m_distancesDanger[3] = std::make_pair(0.0, "DOWNRIGHT");
	m_distancesDanger[4] = std::make_pair(0.0, "DOWN");
	m_distancesDanger[5] = std::make_pair(0.0, "DOWNLEFT");
	m_distancesDanger[6] = std::make_pair(0.0, "LEFT");
	m_distancesDanger[7] = std::make_pair(0.0, "UPLEFT");
}


sf::Vector2f FrayAI::getCurrentNodePosition()
{
	
	sf::Vector2f target;
	target = m_nodes[currentNode].getPosition();

	std::cout << target.x << ", " << target.y << std::endl;

	if (Math::distance(m_position, target) <= 5)
	{
		currentNode += 1;
		if (currentNode >= m_nodes.size()) {
			currentNode = 0;
		}
	}

	/*if (thor::length(target) != 0)
	{
		return target - m_position;
	}
	else
	{
		return sf::Vector2f();
	}*/
	return target;
	//std::cout << target.x << ", " << target.y << std::endl;
}