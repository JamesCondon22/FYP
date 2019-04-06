#include "Menus/DemoScreen.h"
#include <iostream>

DemoScreen::DemoScreen(GameState * state, sf::Font & font, sf::RenderWindow & window):
	m_currentState(state),
	m_font(font)
{
	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level)) {
		return;
	}

	if (!m_textureObs.loadFromFile("resources/assets/obstacle.png")) {

		std::cout << "texture not loading" << std::endl;
	}

	for (ObstacleData const &obs : m_level.m_obstacles) {
		Obstacle* obstacle = new Obstacle(obs.m_radius, m_textureObs, sf::Vector2f(0,0), true);
		obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
		obstacle->setPosition(obs.m_position);
		m_obstacles.push_back(obstacle);
	}

	for (PathData const &path : m_level.m_paths) {
		GameNode * circle = new GameNode(10, m_nodeTexture);
		circle->setPosition(sf::Vector2f(0, 0));
		circle->setOrigin(circle->getRadius(), circle->getRadius());
		circle->setPosition(path.m_position);
		circle->setColor(sf::Color::Red);
		m_nodes.push_back(circle);
	}

	m_aiStates = new BehaviourState;
	*m_aiStates = BehaviourState::ChaseEntity;

	initAI();

	m_file.open("resources/assets/DemoFile.txt");
	m_labelPosition = sf::Vector2f(1500.0f, 50.0f);
	m_aitypeLabel = new Label(m_font, m_labelPosition);
	m_aitypeLabel->setSize(70);

	sf::RectangleShape rect; 
	rect.setPosition(0.0f, 0.0f);
	rect.setSize(sf::Vector2f(650.0f, 2160.0f));
	rect.setOutlineThickness(2.0f);
	rect.setOutlineColor(sf::Color::Black);
	m_bounding.push_back(rect);
	

	m_timeLabel = new Label(m_font, sf::Vector2f(rect.getPosition().x + 50, rect.getPosition().y + 50));
	m_timeLabel->setSize(60);
	m_timeLabel->setText("Time: " + std::to_string(0));

	m_startLabel = new Label(m_font, sf::Vector2f(m_timeLabel->getPosition().x, m_timeLabel->getPosition().y + 200));
	m_startLabel->setSize(40);
	m_startLabel->setText("Press Space to Start Demo.");
}

DemoScreen::~DemoScreen()
{
	
}

/// <summary>
/// handle all the key presses in the demonstration
/// </summary>
void DemoScreen::handleKeys() {
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_pressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_pressed)
	{
		m_startDemonstration = true;

		for (int i = 0; i < m_enemies.size(); i++)
		{
			m_enemies[i]->setState(*m_currentState);
		}
		m_splineAI->setState(*m_currentState);
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt)) {
		m_altPressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LAlt) && !m_altPressed) {
		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (m_enemies[i]->getVisuals()) {
				m_enemies[i]->setVisuals(false);
			}
			else {
				m_enemies[i]->setVisuals(true);
			}
		}
		if (m_splineAI->getVisuals()) {
			m_splineAI->setVisuals(false);
		}
		else {
			m_splineAI->setVisuals(true);
		}
		if (m_testBot->getVisuals()) {
			m_testBot->setVisuals(false);
		}
		else {
			m_testBot->setVisuals(true);
		}
		m_altPressed = true;
	}

}


void DemoScreen::update(double dt, int id, std::string lastBtnPress)
{
	handleKeys();
	if(!m_startDemonstration) {
		m_startLabel->update();
	}
	if (m_startDemonstration) {

		m_cumulativeTime = m_clock.getElapsedTime().asMilliseconds();

		if (lastBtnPress == "RUN") {

			if (m_splineAI->getId() == id && !m_splineAI->getActive())
			{
				m_ghostAI->setActive(true);
				m_splineAI->setActive(true);
				m_aitypeLabel->setText(m_splineAI->getName());
				m_aitypeLabel->setColor(m_splineAI->getColor());
			}
		}
		else if (lastBtnPress == "RUN ALL") {

			if (m_splineAI->getId() == m_id && !m_splineAI->getActive())
			{
				m_ghostAI->setActive(true);
				m_splineAI->setActive(true);
				m_ghostAI->resetCurve();
				m_aitypeLabel->setText(m_splineAI->getName());
				m_aitypeLabel->setColor(m_splineAI->getColor());
			}
		}
		else if (lastBtnPress == "COMPARE") {

			if (!m_splineAI->getActive() && !m_splineAI->getCollided()) {
				m_ghostAI->setActive(true);
				m_ghostAI->resetCurve();
				m_splineAI->setActive(true);
			}
		}
		
		m_testBot->update(dt);

		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (lastBtnPress == "RUN") {
				checkRun(m_enemies[i], id);
			}
			else if (lastBtnPress == "RUN ALL") {
				checkRunAll(m_enemies[i]);
			}
			else if (lastBtnPress == "COMPARE") {
				checkCompare(m_enemies[i]);
			}
			
			if (m_cumulativeTime > MAX_TIME) {

				if (m_enemies[i]->getActive()) {

					m_enemies[i]->update(dt, m_testBot->getPosition());
					m_timeLabel->setText("Time: " + std::to_string(m_enemies[i]->getTime()));
					checkCollision(m_testBot, m_enemies[i], lastBtnPress);
					if (m_enemies[i]->getCollided()) {
						m_timeLabel->setText("Time: " + std::to_string(0));
						break;
					}
				}

			}
		}	
		if (m_cumulativeTime > MAX_TIME) {

			if (m_splineAI->getActive()) {
		
				m_splineAI->update(dt, m_testBot->getPosition());
				m_timeLabel->setText("Time: " + std::to_string(m_splineAI->getTime()));
				checkSplineCollision(m_testBot, m_splineAI, lastBtnPress);
			}
		}
		if (m_cumulativeTime > GHOST_TIME) {

			if (m_splineAI->getActive()) {
				m_splineAI->setCurve(m_ghostAI->getCurve());
				m_ghostAI->updatePlotPoints(dt, m_testBot->getPosition());
			}
		}

		
	}
	else 
	{
		m_clock.restart();
	}
}


void DemoScreen::resetDemo() {

	m_startDemonstration = false;
	m_id = 1;
	m_counter = 0;
	m_timeLabel->setText("Time: " + std::to_string(0));

	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->setPosition(sf::Vector2f(2700.0f, 300.0f));
		m_enemies[i]->resetDemo();
		m_enemies[i]->setCollided(false);
	}
	m_splineAI->setPosition(sf::Vector2f(2700.0f, 300.0f));
	m_splineAI->setCollided(false);
	m_splineAI->resetDemo();
	m_ghostAI->setPosition(sf::Vector2f(2700.0f, 300.0f));
	m_ghostAI->resetDemo();
}


void DemoScreen::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->render(window);
	}

	/*for (auto & node : m_nodes)
	{
		node->render(window);
	}
*/
	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->getActive())
		{
			m_enemies[i]->render(window);
		}
	}

	if (m_splineAI->getActive())
	{
		m_splineAI->render(window);
	}
	for (auto rect : m_bounding) {

		window.draw(rect);
	}
	m_timeLabel->render(window);
	m_aitypeLabel->render(window);
	if (!m_startDemonstration) {
		m_startLabel->render(window);
	}
	m_testBot->render(window);
}


void DemoScreen::checkSplineCollision(TestBot * bot, CRSplineAI * enemy, std::string lastBtnPress) {

	sf::Vector2f v1 = bot->getPosition();
	sf::Vector2f v2 = enemy->getPos();
	int rad = bot->getRadius();

	if (Math::circleCollision(v1, v2, rad, rad))
	{
		enemy->setCollided(true);
		

		if (lastBtnPress == "RUN")
		{
			enemy->setActive(false);
			bot->reset();
			updateRun();
		}
		else if (lastBtnPress == "RUN ALL")
		{
			m_file << "ID = " << enemy->getId() << " " << enemy->getName() << std::endl;
			m_file << "Path length = " << enemy->getPathLength() << std::endl;
			m_file << "Interception Time = " << enemy->getInterceptionTime() << std::endl;
			m_file << "Average Execution Time = " << enemy->getAverageExecTime() << std::endl;
			m_file << "Total Rotations: " << enemy->getTotalRotation() << std::endl;
			m_file << "\n";

			enemy->setActive(false);
			bot->reset();
			updateRunAll();
		}
		else if (lastBtnPress == "COMPARE")
		{
		
			enemy->setActive(false);
			updateCompare();
		}
	}
}


void DemoScreen::checkCollision(TestBot * bot, Enemy * enemy, std::string lastBtnPress)
{
	sf::Vector2f v1 = bot->getPosition();
	sf::Vector2f v2 = enemy->getPos();
	int rad = bot->getRadius();

	if (Math::circleCollision(v1, v2, rad, rad))
	{
		enemy->setCollided(true);
		
		if (lastBtnPress == "RUN")
		{
			enemy->setActive(false);
			bot->reset();
			updateRun();
		}
		else if (lastBtnPress == "RUN ALL")
		{
			m_file << "ID:  " << enemy->getId() << " " << enemy->getName() << std::endl;
			m_file << "Path length: " << enemy->getPathLength() << std::endl;
			m_file << "Interception Time: " << enemy->getInterceptionTime() << std::endl;
			m_file << "Average Execution Time: " << enemy->getAverageExecTime() << std::endl;
			m_file << "Total Rotations: " << enemy->getTotalRotation() << std::endl;
			m_file << "\n";

			enemy->setActive(false);
			bot->reset();
			updateRunAll();

		}
		else if (lastBtnPress == "COMPARE")
		{
			m_counter += 1;
			enemy->setActive(false);
			updateCompare();
		}
	}
}

/// <summary>
/// initialises all the AI characters
/// sets the Behaviour state
/// adds to the enemies vector
/// </summary>
void DemoScreen::initAI()
{
	Enemy * aiOne = new FrayAI(m_nodes, m_obstacles);
	Enemy * aiTwo = new InterpolatingAI(m_nodes, m_obstacles);
	Enemy * aiThree = new EfficiencyAI(m_nodes, m_obstacles);
	Enemy * aiFour = new InterpolatingTwo(m_nodes, m_obstacles);
	Enemy * aiFive = new DynamicVectorAI(m_nodes, m_obstacles);
	Enemy * aiSix = new Traditional(m_nodes, m_obstacles);
	
	m_splineAI = new CRSplineAI(m_nodes, m_obstacles);
	m_testBot = new TestBot(m_nodes, m_obstacles);
	m_ghostAI = new CRSplineAI(m_nodes, m_obstacles);

	aiOne->setBehaviourState(m_aiStates);
	aiTwo->setBehaviourState(m_aiStates);
	aiThree->setBehaviourState(m_aiStates);
	aiFour->setBehaviourState(m_aiStates);
	aiFive->setBehaviourState(m_aiStates);
	aiSix->setBehaviourState(m_aiStates);
	m_splineAI->setBehaviourState(m_aiStates);
	m_ghostAI->setBehaviourState(m_aiStates);

	m_enemies.push_back(aiOne);
	m_enemies.push_back(aiTwo);
	m_enemies.push_back(aiThree);
	m_enemies.push_back(aiFour);
	m_enemies.push_back(aiFive);
	m_enemies.push_back(aiSix);
}


void DemoScreen::checkRun(Enemy * enemy, int id) {
	if (!enemy->getActive() && enemy->getId() == id)
	{
		enemy->setActive(true);
		m_aitypeLabel->setText(enemy->getName());
		m_aitypeLabel->setColor(enemy->getColor());
	}
}


void DemoScreen::checkRunAll(Enemy * enemy) {
	if (!enemy->getActive() && enemy->getId() == m_id)
	{
		enemy->setActive(true);
		m_aitypeLabel->setText(enemy->getName());
		m_aitypeLabel->setColor(enemy->getColor());
	}
}


void DemoScreen::checkCompare(Enemy * enemy) {
	if (!enemy->getActive() && !enemy->getCollided())
	{
		enemy->setActive(true);
		m_aitypeLabel->setText("All AI Characters");
	}
}

void DemoScreen::updateRun() {
	resetDemo();
	m_ghostAI->resetCurve();
	*m_currentState = GameState::Options;
}


void DemoScreen::updateRunAll() {

	m_id++;
	m_clock.restart();
	if (m_id > MAX_AI)
	{
		m_file.close();
		resetDemo();
		m_aitypeLabel->setText("");
		*m_currentState = GameState::Options;
	}
}


void DemoScreen::updateCompare() {

	m_counter += 1;
	if (m_counter >= 7) {
		resetDemo();
		m_aitypeLabel->setText("");
		*m_currentState = GameState::Options;
	}
}