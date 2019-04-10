#include "Headers/CRSpline.h"

double const CRSplineAI::RAD_TO_DEG = 180.0f / 3.14;
double const CRSplineAI::DEG_TO_RAD = 3.14 / 180.0f;
CRSplineAI::CRSplineAI(std::vector<GameNode*>  path, std::vector<Obstacle*>  obs) :
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

	m_color = sf::Color::Yellow;
	m_rect.setFillColor(m_color);
	m_rotation = 90;
	m_rect.setRotation(m_rotation);

	m_curve = new CatmullRom();
	m_curve->set_steps(10);


}


CRSplineAI::~CRSplineAI()
{
}

/// <summary>
/// update the the distnaces in the context map 
/// sets the current position and velocity of the AI
/// </summary>
/// <param name="dt">delta time </param>
/// <param name="position">target position</param>
void CRSplineAI::update(double dt, sf::Vector2f position)
{
	m_lastRotation = m_rotation;

	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}
	
	
	if (checkDistance(position) < 200) {
		m_inRange = true;
	}

	if (m_inRange) {
		updateLines(position);
	}
	else {
		updateLines(getPointPosition());
	}
	
	updateDangers();
	m_distances = normalize(m_distances);
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
		handleTimer();
		m_tickCounter += 1;
		calculateRotations();
	}

}

/// <summary>
/// calculates the total amount of rotations made 
/// by the AI character
/// </summary>
void CRSplineAI::calculateRotations() {

	auto currentRotation = m_rotation;

	auto diff = abs(currentRotation - m_lastRotation);

	m_totalRotations += diff;
}

double CRSplineAI::getAverageRotations() {
	return m_totalRotations / m_currentTime;
}

/// <summary>
/// update call for the ghost AI character 
/// creates a spline points every 25 ticks 
/// </summary>
/// <param name="dt">delta time </param>
/// <param name="position">the target position </param>
void CRSplineAI::updatePlotPoints(double dt, sf::Vector2f position)
{
	//checks the ticks 
	if (m_counter == 25) {
		//creates a spline point 
		sf::CircleShape circle(5);
		circle.setPosition(0, 0);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(m_position);
		m_curve->add_way_point(Vector(circle.getPosition().x, circle.getPosition().y, 0));
		m_romPoints.push_back(circle);
		m_counter = 0;
	}
	//updates the ticks 
	m_counter += 1;

	for (int i = 0; i < m_size; i++) {
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}
	//updates the vector lines 
	updateLines(position);
	//updates the dangers 
	updateDangers();
	m_distances = normalize(m_distances);
	//passes the distances from interests and dangers to the Context Map class 
	mapDecisions.update(m_distances, m_distancesDanger);
	//sets the direction for the AI character 
	checkDirection();
	//updates the steering 
	m_steering = seek(position);
	m_position += m_steering.linear;
	m_position = sf::Vector2f(m_position.x + std::cos(DEG_TO_RAD  * (m_rotation)) * m_speed * (dt / 1000),
	m_position.y + std::sin(DEG_TO_RAD * (m_rotation)) * m_speed* (dt / 1000));
	m_rect.setPosition(m_position);
	m_surroundingCircle.setPosition(m_position);
	//updates the ticks 
	m_tickCounter += 1;
	
}

/// <summary>
/// sets the position 
/// </summary>
/// <param name="position"></param>
void CRSplineAI::setPosition(sf::Vector2f position) {
	m_position = position;
	m_rect.setPosition(m_position);
}

/// <summary>
/// gets the closest position of the closest node 
/// sets the target to the noode position
/// </summary>
/// <returns></returns>
sf::Vector2f CRSplineAI::getPointPosition()
{
	sf::Vector2f  target;

	target.x = m_curve->node(currentNode).x;
	target.y = m_curve->node(currentNode).y;

	//checks the distnace between current position and the target
	if (Math::distance(m_position, target) <= 50)
	{
		
		currentNode += 1;
		m_savedNode = currentNode;
	}

	return target;
}

/// <summary>
/// renders the path, AI and 
/// catmull rom points 
/// </summary>
/// <param name="window"></param>
void CRSplineAI::render(sf::RenderWindow & window)
{
	//only renders the path in the demo.
	if (m_state == GameState::Demo) {
		for (int i = 0; i < m_pathLine.size(); i++)
		{
			m_pathLine[i]->render(window);
		}
	}
	//checks if the visuals are on
	if (m_visuals) {
		for (int i = 0; i < m_size; i++) {
			m_lineVec[i].render(window);
		}
		window.draw(m_surroundingCircle);
	}
	//draws the rom points 
	for (auto &rom : m_romPoints) {
		window.draw(rom);
	}

	window.draw(m_rect);

}

/// <summary>
/// checks the distance between the AI character 
/// and the target
/// </summary>
/// <param name="position">position of the target</param>
/// <returns></returns>
double CRSplineAI::checkDistance(sf::Vector2f position) {

	return Math::distance(m_position, position);
}

/// <summary>
/// gets the current position
/// </summary>
/// <returns></returns>
sf::Vector2f CRSplineAI::getPos()
{
	return m_position;
}

/// <summary>
/// gets the velocity
/// </summary>
/// <returns></returns>
sf::Vector2f CRSplineAI::getVel()
{
	return m_velocity;
}

/// <summary>
/// updates the directional vectors in relation to the 
/// position being passed 
/// </summary>
/// <param name="position"></param>
void CRSplineAI::updateLines(sf::Vector2f position)
{
	int count = 0;

	//loops throught the vectors checking the current distance from each 
	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it) {
		m_distances[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), position);
		count++;
	}
}

/// <summary>
/// updates the dangers, checks which is the closest danger 
/// and updates the vectors in relation to the closest
/// </summary>
void CRSplineAI::updateDangers()
{
	int count = 0;
	//initialises an obstacle 
	Obstacle *obs = new Obstacle(0);
	double smallest = 10000000;
	//loops through the obstacles searching for the smallest
	for (auto it = m_obstacles.begin(); it != m_obstacles.end(); ++it)
	{
		double dist = Math::distance(m_position, (*it)->getPosition());
		if (dist < smallest)
		{
			obs = (*it);
			smallest = dist;
		}
	}
	/// <summary>
	/// updates the lines in relation to the closest obstacle 
	/// </summary>
	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{

		m_distancesDanger[it->getState()] = Math::distance(sf::Vector2f(m_lineVec[count].getPosition().x, m_lineVec[count].getPosition().y), obs->getPosition());
		//checkdistance
		count++;
	}

}

/// <summary>
/// finds the largest value in the map
/// and returns  
/// </summary>
/// <param name="vec">Direction map</param>
/// <returns></returns>
double CRSplineAI::findLargest(std::map<Direction, double> vec)
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

/// <summary>
/// normalizes the map to a value between 0 and 1
/// finds the largest value and uses that value to 
/// sort the map
/// </summary>
/// <param name="vec"></param>
/// <returns></returns>
std::map<Direction, double> CRSplineAI::normalize(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = 1 - (it->second / curLargest);

	}

	return vec;
}

/// <summary>
/// normalises the dangers to a value between 0 and 1
/// finds the largert value and divides all values by the largest 
/// </summary>
/// <param name="vec">the distances map</param>
/// <returns></returns>
std::map<Direction, double> CRSplineAI::normalizeDangers(std::map<Direction, double> vec)
{
	auto curLargest = findLargest(vec);

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		vec[it->first] = it->second / curLargest;

	}

	return vec;
}


/// <summary>
/// seek function using dynamic steering 
/// </summary>
/// <param name="position">seek position</param>
/// <returns></returns>
steering CRSplineAI::seek(sf::Vector2f position)
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

/// <summary>
/// calculates the current orientation in regards to 
/// the velocity vector and updates the speed 
/// </summary>
void CRSplineAI::calculation() {

	if (m_velocity.x != 0 || m_velocity.y != 0)
	{
		float magnitude = mag(m_velocity);
		m_velocity = sf::Vector2f(m_velocity.x / magnitude, m_velocity.y / magnitude);
		m_velocity = m_velocity * m_speed;
		m_rotation = getNewOrientation(m_rotation, m_velocity);
	}
}

/// <summary>
/// calculates the magnitude of the vector 
/// </summary>
/// <param name="v">vector v</param>
/// <returns></returns>
float CRSplineAI::mag(sf::Vector2f & v)
{
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}


/// <summary>
/// calculates the current orientation of the 
/// AI character depending on the velocity
/// </summary>
/// <param name="curOrientation">the current rotation</param>
/// <param name="velocity">the velocity of the AI </param>
/// <returns></returns>
float CRSplineAI::getNewOrientation(float curOrientation, sf::Vector2f velocity)
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
/// calculates the length of a vector 
/// </summary>
/// <param name="vel">the velocity</param>
/// <returns>float</returns>
float CRSplineAI::length(sf::Vector2f vel) {
	return sqrt(vel.x * vel.x + vel.y * vel.y);
}

/// <summary>
/// sets the current direction for the AI 
/// this direction depends on the closest vector to target position
/// </summary>
void CRSplineAI::checkDirection()
{
	auto tempDirection = curDirection;

	for (auto it = m_lineVec.begin(); it != m_lineVec.end(); ++it)
	{
		//checks the strongest entry in the map
		if (mapDecisions.getStrongest() == it->getState()) {
			m_futurePos = it->getMap()[mapDecisions.getStrongest()];
			it->changeColor();
		}
	}
	//uses a linear interpolation between the two positions 
	curDirection = Math::lerp(tempDirection, m_futurePos, 0.08);
}

/// <summary>
/// inilialises the map giving each entry a direction 
/// and a value of 0.0, inits both the distances from interests 
/// and the distances from dangers 
/// </summary>
void CRSplineAI::initVector() {

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

/// <summary>
/// gets the position of the closest node 
/// only checks the nodes which have not been completed or alive 
/// </summary>
/// <returns></returns>
sf::Vector2f CRSplineAI::getCurrentNodePosition()
{
	sf::Vector2f target;

	double smallest = DBL_MAX;
	auto curIndex = 0;

	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (!m_nodes[i]->getCompleted()) {
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
/// finds the closest node 
/// checks the distance of each node and 
/// sets the index to the closest node position
/// </summary>
void CRSplineAI::findClosestNode() {

	double smallest = DBL_MAX;
	auto curIndex = 0;

	for (int i = 0; i < m_nodes.size(); i++) {
		//only checks the nodes which have not been colleceted 
		if (m_nodes[i]->getAlive()) {
			auto dist = Math::distance(m_position, m_nodes[i]->getPosition());
			//checks for the smallest
			if (dist < smallest) {
				smallest = dist;
				curIndex = i;
			}
		}
	}
	m_closestNode = curIndex; 
}

/// <summary>
/// normalises the vector to a value between 0 and 1
/// </summary>
/// <param name="vec">the vector </param>
/// <returns></returns>
sf::Vector2f CRSplineAI::normalize(sf::Vector2f vec)
{
	if (vec.x*vec.x + vec.y * vec.y != 0)
	{
		vec.x = vec.x / sqrt(vec.x*vec.x + vec.y * vec.y);
		vec.y = vec.y / sqrt(vec.x*vec.x + vec.y * vec.y);
	}
	return vec;
}

/// <summary>
/// generates a path or trail which is left 
/// by the ai, updates the path using the dt value 
/// pushes the path into the a vector contaning the path nodes 
/// </summary>
/// <param name="dt">delta time</param>
void CRSplineAI::generatePath(double dt) 
{
	//updates the amount
	m_timeAmount += dt;

	if (m_timeAmount > 150) {

		Path * circle = new Path(3);
		circle->setPosition(m_position);
		circle->setColor(m_color);
		m_pathLine.push_back(circle);
		m_timeAmount = 0;
		
		//calculates the distance between two nodes 
		if (m_lastPathCircle != nullptr) {
			//adds the distnace to the total value 
			auto dist = Math::distance(m_lastPathCircle->getPosition(), circle->getPosition());
			m_totalPathLength += dist;
		}

		m_lastPathCircle = circle;
	}
}

/// <summary>
/// updates the time 
/// </summary>
void CRSplineAI::handleTimer() {
	//resets the clock 
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
/// <returns></returns>
double CRSplineAI::getAverageExecTime()
{
	m_averageExecTime = (m_currentTime * 1000) / m_tickCounter;
	return m_averageExecTime;
}


/// <summary>
/// resets all the game data 
/// </summary>
void CRSplineAI::resetGame() {
	for (int i = 0; i < m_nodes.size(); i++) {

		m_nodes[i]->setCompleted(false);
		m_nodes[i]->setAlive(true);
	}
}

/// <summary>
/// resets all the data in relation to 
/// the demo 
/// </summary>
void CRSplineAI::resetDemo() {

	m_lastPathCircle = nullptr;
	m_timeAmount = 0;
	currentNode = 0;
	m_counter = 0;
	m_pathLine.clear();
	m_romPoints.clear();
	m_startTimer = false;
	m_currentTime = 0;
	m_tickCounter = 0;
	m_totalRotations = 0;
	m_totalPathLength = 0;
	m_inRange = false;
	m_rotation = 90;
	m_rect.setRotation(m_rotation);
	m_surroundingCircle.setPosition(m_position);
	
	for (int i = 0; i < m_size; i++)
	{
		m_lineVec[i].update(m_surroundingCircle.getPosition());
	}
}

/// <summary>
/// clears the catmull  ro plot points 
/// </summary>
void CRSplineAI::resetCurve() {

	m_curve->clear();
}