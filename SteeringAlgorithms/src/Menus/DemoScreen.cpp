#include "Menus/DemoScreen.h"
#include <iostream>

DemoScreen::DemoScreen(GameState * state):
	m_currentState(state)
{

	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level)) {
		return;
	}

	if (!m_textureObs.loadFromFile("resources/assets/obstacle.png")) {
		std::cout << "texture not loading" << std::endl;
	}

	for (ObstacleData const &obs : m_level.m_obstacles) {
		Obstacle* obstacle = new Obstacle(obs.m_radius, m_textureObs);
		obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
		obstacle->setID(obs.m_id);
		obstacle->setPosition(obs.m_position);
		m_obstacles.push_back(obstacle);
	}

	for (PathData const &path : m_level.m_paths) {
		sf::CircleShape circle(10);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		circle.setFillColor(sf::Color::Red);
		m_nodes.push_back(circle);
	}

	m_player = new Player();
	m_trad = new Traditional(m_nodes, m_obstacles);
	m_testBot = new TestBot(m_nodes, m_obstacles);

	Enemy * aiOne = new FrayAI(m_nodes, m_obstacles);
	Enemy * aiTwo = new InterpolatingAI(m_nodes, m_obstacles);
	Enemy * aiThree = new EfficiencyAI(m_nodes, m_obstacles);
	Enemy * aiFour = new InterpolatingTwo(m_nodes, m_obstacles);
	Enemy * aiFive = new DynamicVectorAI(m_nodes, m_obstacles);

	m_enemies.push_back(aiOne);
	m_enemies.push_back(aiTwo);
	m_enemies.push_back(aiThree);
	m_enemies.push_back(aiFour);
	m_enemies.push_back(aiFive);

	m_file.open("resources/assets/DemoFile.txt");
}

DemoScreen::~DemoScreen()
{
	
}


void DemoScreen::update(double dt, int id)
{
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		m_pressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && !m_pressed)
	{
		m_startDemonstration = true;
	}
	
	m_player->update(dt);
	
	if (m_startDemonstration) {

		m_cumulativeTime += m_clock.restart().asMilliseconds();

		m_testBot->update(dt);

		for (int i = 0; i < m_enemies.size(); i++)
		{
			if (!m_enemies[i]->getActive() && m_enemies[i]->getId() == id)
			{
				m_enemies[i]->setActive(true);
			}
			if (m_cumulativeTime > MAX_TIME) {

				if (m_enemies[i]->getActive())
				{
					m_enemies[i]->update(dt, m_testBot->getPosition());

					checkCollision(m_testBot, m_enemies[i]);
				}
				
			}

		}
		
	}
	else
	{
		m_clock.restart() = sf::Time::Zero;
	}
}

void DemoScreen::render(sf::RenderWindow & window)
{
	m_player->render(window);

	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->render(window);
	}

	for (auto &node : m_nodes)
	{
		window.draw(node);
	}

	for (int i = 0; i < m_enemies.size(); i++)
	{
		if (m_enemies[i]->getActive())
		{
			m_enemies[i]->render(window);
		}
	}

	m_testBot->render(window);
}


void DemoScreen::checkCollision(TestBot * bot, Enemy * enemy)
{
	sf::Vector2f v1 = bot->getPosition();
	sf::Vector2f v2 = enemy->getPos();
	int rad = bot->getRadius();

	if (Math::circleCollision(v1, v2, rad, rad))
	{
		m_file << enemy->getId() << ": " << enemy->getPathLength();
		m_file.close();

		*m_currentState = GameState::Options;
	}

}

