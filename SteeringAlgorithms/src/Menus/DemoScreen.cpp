#include "Menus/DemoScreen.h"
#include <iostream>

DemoScreen::DemoScreen(GameState * state, sf::Font & font):
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
		obstacle->setID(obs.m_id);
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
	m_labelPosition = sf::Vector2f(100.0f, 50.0f);
	m_aitypeLabel = new Label(m_font, m_labelPosition);
	m_aitypeLabel->setSize(30);


	
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

	if (m_startDemonstration) {

		m_cumulativeTime = m_clock.getElapsedTime().asMilliseconds();

		if (lastBtnPress == "RUN") {
			if (m_splineAI->getId() == id) {
				m_ghostAI->updatePlotPoints(dt, m_testBot->getPosition());
			}

			if (m_splineAI->getId() == id && !m_splineAI->getActive())
			{
				m_splineAI->setActive(true);
				m_aitypeLabel->setText(m_splineAI->getName());
				m_aitypeLabel->setColor(m_splineAI->getColor());
			}
		}
		else if (lastBtnPress == "RUNALL") {
			
			if (m_splineAI->getId() == m_id) {
				m_ghostAI->updatePlotPoints(dt, m_testBot->getPosition());
			}

			if (m_splineAI->getId() == m_id && !m_splineAI->getActive())
			{
				m_splineAI->setActive(true);
				m_aitypeLabel->setText(m_splineAI->getName());
				m_aitypeLabel->setColor(m_splineAI->getColor());
			}
		}
		else if (lastBtnPress == "COMPARE") {
			
			m_ghostAI->updatePlotPoints(dt, m_testBot->getPosition());

			if (!m_splineAI->getActive()) {
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
					checkCollision(m_testBot, m_enemies[i], lastBtnPress);
				}

			}
		}	
		if (m_cumulativeTime > MAX_TIME) {

			if (m_splineAI->getActive()) {
		
				m_splineAI->setCurve(m_ghostAI->getCurve());
				m_splineAI->update(dt, m_testBot->getPosition());
			}
		}
	}
	else 
	{
		m_clock.restart();
	}
}


void DemoScreen::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->render(window);
	}

	for (auto & node : m_nodes)
	{
		node->render(window);
	}

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
		m_ghostAI->render(window);
	}

	m_aitypeLabel->render(window);
	m_testBot->render(window);
}


void DemoScreen::checkCollision(TestBot * bot, Enemy * enemy, std::string lastBtnPress)
{
	sf::Vector2f v1 = bot->getPosition();
	sf::Vector2f v2 = enemy->getPos();
	int rad = bot->getRadius();

	if (Math::circleCollision(v1, v2, rad, rad))
	{
		enemy->setCollided(true);
		m_file << "ID = " << enemy->getId() << " " << enemy->getName() << std::endl;
		m_file << "Path length = " << enemy->getPathLength() << std::endl;
		m_file << "Interception Time = " << enemy->getInterceptionTime() << std::endl;
		m_file << "Average Execution Time = " << enemy->getAverageExecTime()  << std::endl;
		m_file << "\n";
		
		
		if (lastBtnPress == "RUN")
		{
			m_file.close();
			*m_currentState = GameState::Options;
		}
		else if (lastBtnPress == "RUN ALL")
		{
			m_id++;
			enemy->setActive(false);
			bot->reset();
			m_clock.restart();
			if (m_id > 7)
			{
				m_file.close();
				*m_currentState = GameState::Options;
			}
		}
		else if (lastBtnPress == "COMPARE")
		{
			enemy->setActive(false);
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
	}
}