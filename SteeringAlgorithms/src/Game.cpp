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



	m_currentState = new GameState;
	*m_currentState = (GameState::Demo);


	if (!m_textureEnemy.loadFromFile("resources/assets/enemy.png")) {
		std::cout << "texture not loading" << std::endl;
	}


	m_options = new Options(m_currentState);
	m_demoScreen = new DemoScreen(m_currentState);
	mainMenu = new MainMenu(m_currentState);

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

	switch (*m_currentState)
	{
	case GameState::None:
		break;
	case GameState::Menu:
		mainMenu->update(dt);
		break;
	case GameState::Demo:
		m_demoScreen->update(dt);
		break;
	case GameState::Options:
		m_options->update(dt);
		break;
	default:
		break;
	}
}


/// <summary>
/// @brief draw the window for the game.
/// 
/// draw buttons and text on left side
/// </summary>
void Game::render()
{
	m_window.clear(sf::Color(211, 211, 211));
	
	switch (*m_currentState)
	{
	case GameState::None:
		break;
	case GameState::Menu:
		mainMenu->render(m_window);
		break;
	case GameState::Demo:
		m_demoScreen->render(m_window);
		break;
	case GameState::Options:
		m_options->render(m_window);
		break;
	default:
		break;
	}
	
	m_window.display();
}


