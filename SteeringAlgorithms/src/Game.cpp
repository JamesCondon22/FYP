#include "../Include/Headers/Game.h"

/// <summary>
/// @author RP
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
Game::Game()
	: m_window(sf::VideoMode(1920, 1080, 32), "SFML Playground", sf::Style::Default)

{

	m_window.setVerticalSyncEnabled(true);
	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level)) {
		return;
	}

	if (!m_texture.loadFromFile("resources/assets/obstacle.png")) {
		std::cout << "texture not loading" << std::endl;
	}

	

	for (ObstacleData const &obs : m_level.m_obstacles) {
		Obstacle* obstacle = new Obstacle(obs.m_radius, m_texture);
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
	m_ai = new FrayAI(m_nodes, m_obstacles);
	m_interAI = new InterpolatingAI(m_nodes, m_obstacles);
	m_efficAI = new EfficiencyAI(m_nodes, m_obstacles);
	m_interTwo = new InterpolatingTwo(m_nodes, m_obstacles);
	m_dynamAI = new DynamicVectorAI(m_nodes, m_obstacles);
}



/// <summary>
/// Main game entry point - runs until user quits.
/// </summary>
void Game::run()
{
	sf::Clock clock;
	sf::Int32 lag = 0;

	while (m_window.isOpen())
	{
		sf::Time dt = clock.restart();

		lag += dt.asMilliseconds();

		processEvents();

		while (lag > MS_PER_UPDATE)
		{
			update(MS_PER_UPDATE);
			lag -= MS_PER_UPDATE;
		}
		update(MS_PER_UPDATE);

		render();
	}
}



/// <summary>
/// @brief Check for events
/// 
/// Allows window to function and exit. 
/// Events are passed on to the Game::processGameEvents() method
/// </summary>
void Game::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_window.close();
		}
		processGameEvents(event);
	}
}
/// <summary>
/// @brief Handle all user input.
/// 
/// Detect and handle keyboard input.
/// </summary>
/// <param name="event">system event</param>
void Game::processGameEvents(sf::Event& event)
{


}

/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;

	m_player->update(dt);
	//m_trad->update(dt,m_player->getPos(), m_player->getVel());
	//m_ai->update(dt, m_trad->getPosition());
	//m_interAI->update(dt, m_trad->getPosition());
	//m_efficAI->update(dt, m_trad->getPosition());
	//m_interTwo->update(dt, m_trad->getPosition());
	m_dynamAI->update(dt, m_trad->getPosition());
}








/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(211, 211, 211));
	m_player->render(m_window);
	
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->render(m_window);
	}

	for (auto &node : m_nodes)
	{
		m_window.draw(node);
	}
	//m_trad->render(m_window);
	//m_ai->render(m_window);
	//m_interAI->render(m_window);
	//m_efficAI->render(m_window);
	//m_interTwo->render(m_window);
	m_dynamAI->render(m_window);
	m_window.display();
}


