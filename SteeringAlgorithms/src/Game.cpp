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

	*m_currentState = GameState::MainMenu;
	ImGui::SFML::Init(m_window);
	if (!m_textureEnemy.loadFromFile("resources/assets/enemy.png")) {
		std::cout << "texture not loading" << std::endl;
	}
	m_backgroundTexture.loadFromFile("resources/assets/background.jpg");
	m_backgroundSprite.setSize(sf::Vector2f((float)window_width, (float)window_height));
	m_backgroundSprite.setTexture(&m_backgroundTexture);

	m_buttonTexture.loadFromFile("resources/assets/button.png");
	m_font.loadFromFile("resources/assets/bernhc.TTF");
	m_fontBell.loadFromFile("resources/assets/Crimson-Bold.TTF");
	m_options = new Options(m_currentState, m_font, m_fontBell, m_buttonTexture, m_window);
	m_demoScreen = new DemoScreen(m_currentState, m_fontBell, m_window);
	m_mainMenu = new MainMenu(m_currentState, m_fontBell);
	m_menu = new Menu(m_currentState, m_fontBell);
	m_gameScreen = new GameScreen(m_currentState, size, m_fontBell, m_window);
	m_endGameScreen = new EndGame(m_currentState, m_fontBell);
	m_gameMenu = new GameMenu(m_currentState, m_font, m_fontBell);
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
		m_mainMenu->m_pressed = false;
		m_menu->m_pressed = false;
		m_gameMenu->m_pressed = false;
		m_endGameScreen->m_pressed = false;
		m_options->m_pressed = false;
	
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
	
	ImGui::SFML::Update(m_window, m_clock.restart());

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
		m_endGameScreen->update(dt, m_window);
		break;
	case GameState::Options:
		m_options->update(dt);
		updateGUI();
		break;
	default:
		break;
	}

	ImGui::EndFrame();
}

/// <summary>
/// updates the Graphs which represent the data 
/// retrieved fromt the demonstration 
/// </summary>
void Game::updateGUI() {
	
	calculateGraphData();

	ImGui::Begin("Interception Time");
	ImGui::DrawLine(ImVec2(80, 70), ImVec2(80, 870), sf::Color::White, 2.0f);
	ImGui::SetCursorPos(ImVec2(100.0f, 100.0f));
	ImGui::PlotHistogram("", m_InterTarr, IM_ARRAYSIZE(m_InterTarr), 0, NULL, 0.0f, 20.0f, ImVec2(1200, 800.0f));
	ImGui::DrawLine(ImVec2(80, 0), ImVec2(1300, 0), sf::Color::White, 2.0f);
	initText();
	ImGui::End();

	ImGui::Begin("Average Execution Time");
	ImGui::DrawLine(ImVec2(80, 70), ImVec2(80, 870), sf::Color::White, 2.0f);
	ImGui::SetCursorPos(ImVec2(100.0f, 100.0f));
	ImGui::PlotHistogram("", m_AETarr, IM_ARRAYSIZE(m_AETarr), 0, NULL, 0.0f, 5.0f, ImVec2(1200, 800.0f));
	ImGui::DrawLine(ImVec2(80, 0), ImVec2(1300, 0), sf::Color::White, 2.0f);
	initText();
	ImGui::End();


	ImGui::Begin("Path Lengths");
	ImGui::DrawLine(ImVec2(80, 70), ImVec2(80, 870), sf::Color::White, 2.0f);
	ImGui::SetCursorPos(ImVec2(100.0f, 100.0f));
	ImGui::PlotHistogram("", m_pathArr, IM_ARRAYSIZE(m_pathArr), 0, NULL, 0.0f, 10000.0f, ImVec2(1200, 800.0f));
	ImGui::DrawLine(ImVec2(80, 0), ImVec2(1300, 0), sf::Color::White, 2.0f);
	initText();
	ImGui::End();

	ImGui::Begin("Total Rotations");
	ImGui::DrawLine(ImVec2(80, 70), ImVec2(80, 870), sf::Color::White, 2.0f);
	ImGui::SetCursorPos(ImVec2(100.0f, 100.0f));
	ImGui::PlotHistogram("", m_rotationsArr, IM_ARRAYSIZE(m_rotationsArr), 0, NULL, 0.0f, 10000.0f, ImVec2(1200, 800.0f));
	ImGui::DrawLine(ImVec2(80, 0), ImVec2(1300, 0), sf::Color::White, 2.0f);
	initText();
	ImGui::End();

	ImGui::Begin("Average Rotations p/s");
	ImGui::DrawLine(ImVec2(80, 70), ImVec2(80, 870), sf::Color::White, 2.0f);
	ImGui::SetCursorPos(ImVec2(100.0f, 100.0f));
	ImGui::PlotHistogram("", m_AvgRotationsArr, IM_ARRAYSIZE(m_AvgRotationsArr), 0, NULL, 0.0f, 1000.0f, ImVec2(1200, 800.0f));
	ImGui::DrawLine(ImVec2(80, 0), ImVec2(1300, 0), sf::Color::White, 2.0f);
	initText();
	ImGui::End();

}


void Game::initText() {

	ImGui::SetWindowFontScale(1.5f);
	ImGui::SetCursorPos(ImVec2(110, 920));
	ImGui::Text("Basic Context");

	ImGui::SetCursorPos(ImVec2(280, 920));
	ImGui::Text("   Average \nInterpolation");

	ImGui::SetCursorPos(ImVec2(460, 920));
	ImGui::Text("   Blended \nInterpolation");

	ImGui::SetCursorPos(ImVec2(650, 920));
	ImGui::Text("Efficiency");

	ImGui::SetCursorPos(ImVec2(800, 920));
	ImGui::Text("Dynamic Vector");

	ImGui::SetCursorPos(ImVec2(980, 920));
	ImGui::Text("Catmull Rom");

	ImGui::SetCursorPos(ImVec2(1160, 920));
	ImGui::Text("Traditional");
}


void Game::calculateGraphData() {
	
	for (int i = 0; i < 7; i++) {
		m_AETarr[i] = m_demoScreen->getAETimes()[i];
	}
		
	for (int i = 0; i < 7; i++) {
		m_InterTarr[i] = m_demoScreen->getInterceptionTimes()[i];
	}

	for (int i = 0; i < 7; i++) {
		m_pathArr[i] = m_demoScreen->getPathLengths()[i];
	}
	
	for (int i = 0; i < 7; i++) {
		m_rotationsArr[i] = m_demoScreen->getRotations()[i];
	}

	for (int i = 0; i < 7; i++) {
		m_AvgRotationsArr[i] = m_demoScreen->getAverageRotations()[i];
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
	m_window.draw(m_backgroundSprite);
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
		ImGui::SFML::Render(m_window);
		break;
	default:
		break;
	}
	m_window.display();
}


