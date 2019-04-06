#include "../Include/Headers/Game.h"

/// <summary>
/// @author RP
/// @version 1.0
/// 
/// </summary>

// Updates per milliseconds
static double const MS_PER_UPDATE = 10.0;
sf::VideoMode desktop = sf::VideoMode::getDesktopMode();
const int window_height = desktop.height;
const int window_width = desktop.width;

/// <summary>
/// @brief Default constructor.
/// 
/// Create a new window and initialise member objects.
/// </summary>
/// 
/// 
Game::Game() :
	m_window(sf::VideoMode(desktop.width, desktop.height, desktop.bitsPerPixel), "FYP", sf::Style::Default)
{
	sf::Vector2f size = sf::Vector2f((float)window_width, (float)window_height);

	m_currentState = new GameState;

	*m_currentState = GameState::Menu;

	if (!m_textureEnemy.loadFromFile("resources/assets/enemy.png")) {
		std::cout << "texture not loading" << std::endl;
	}
	m_buttonTexture.loadFromFile("resources/assets/button.png");
	m_font.loadFromFile("resources/assets/bernhc.TTF");
	m_fontBell.loadFromFile("resources/assets/Crimson-Bold.TTF");
	m_options = new Options(m_currentState, m_fontBell, m_font, m_buttonTexture, m_window);
	m_demoScreen = new DemoScreen(m_currentState, m_font, m_window);
	m_mainMenu = new MainMenu(m_currentState, m_font);
	m_menu = new Menu(m_currentState);
	m_gameScreen = new GameScreen(m_currentState, size, m_font, m_window);
	m_endGameScreen = new EndGame(m_currentState, m_font);
	m_gameMenu = new GameMenu(m_currentState, m_font);
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
			ImGui::SFML::Shutdown();
			m_window.close();
		}
		ImGui::SFML::ProcessEvent(event);
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
	
	if (event.type == sf::Event::MouseButtonReleased)
	{
		m_pressed = false;
		/*switch (*m_currentState)
		{
		case GameState::None:
			break;
		case GameState::MainMenu:*/
			m_mainMenu->m_pressed = false;
		/*	break;
		case GameState::Menu:*/
			m_menu->m_pressed = false;
		/*	break;
		case GameState::Demo:
			break;
		case GameState::PreGame:*/
			m_gameMenu->m_pressed = false;
			/*break;
		case GameState::GameScreen:
			break;
		case GameState::EndGame:*/
			m_endGameScreen->m_pressed = false;
			/*break;
		case GameState::Options:*/
			m_options->m_pressed = false;
			/*break;
		default:
			break;
		}*/
	}
}


/// <summary>
/// Method to handle all game updates
/// </summary>
/// <param name="time">update delta time</param>
void Game::update(double dt)
{
	sf::Time deltaTime;
	m_mousePosition = sf::Mouse::getPosition(m_window);

	
	switch (*m_currentState)
	{
	case GameState::None:
		break;
	case GameState::MainMenu:
		m_mainMenu->update(dt, m_window);
		break;
	case GameState::Menu:
		m_menu->update(dt, m_window);
		break;
	case GameState::Demo:
		m_window.setVerticalSyncEnabled(false);
		m_demoScreen->update(dt, m_menu->getActivatedAI(), m_menu->getLastPressed());
		break;
	case GameState::PreGame:
		m_gameMenu->update(dt, m_window);
		break;
	case GameState::GameScreen:
		m_window.setVerticalSyncEnabled(true);
		m_gameScreen->update(dt, m_mousePosition);
		break;
	case GameState::EndGame:
		m_endGameScreen->update(dt);
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
	case GameState::MainMenu:
		m_mainMenu->render(m_window);
		break;
	case GameState::Menu:
		m_menu->render(m_window);
		break;
	case GameState::Demo:
		m_demoScreen->render(m_window);
		break;
	case GameState::PreGame:
		m_gameMenu->render(m_window);
		break;
	case GameState::GameScreen:
		m_gameScreen->render(m_window);
		break;
	case GameState::EndGame:
		m_endGameScreen->render(m_window);
		break;
	case GameState::Options:
		m_options->render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}


