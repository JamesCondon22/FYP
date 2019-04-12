#include "Menus/EndGame.h"

EndGame::EndGame(GameState * state, sf::Font & font) :
	m_currentState(state),
	m_position(1500.0f,100.0f),
	m_font(font)
{
	m_texture.loadFromFile("resources/assets/button.png");
	//initialises main menu button
	m_backButton = new Button(sf::Vector2f(2500.0f, 1500.0F), 800, 150, m_texture, m_font, "MAIN MENU");
}


/// <summary>
/// loads the scoreboard text file when the menu opens
/// applies labels to the scores 
/// positions all the text to the screen
/// </summary>
/// <param name="dt"></param>
void EndGame::update(double dt, sf::Window & window) {

	m_mousePosition = sf::Mouse::getPosition(window);

	//reopens the file =
	if (!m_loaded) {
		m_labels.clear();
		m_file.open("resources/assets/scores.txt");
		//header label 
		Label * label = new Label(m_font, sf::Vector2f(1600.0f,m_position.y));
		label->setText("SCOREBOARD.");
		label->setSize(100);
		label->setColor(sf::Color::Black);
		m_position.y += 150.0f;
		m_labels.push_back(label);
	}
	//searches the file and applies labels to the text 
	while (std::getline(m_file, m_line))
	{
		Label * label = new Label(m_font, m_position);
		label->setText(m_line);
		label->setSize(80);
		label->setColor(sf::Color::White);
		label->setOutline(sf::Color::Black, 5.0f);
		m_position.y += 150.0f;
		m_labels.push_back(label);
	}
	//closes file and sets loaded to false
	m_file.close();
	m_loaded = true;
	
	//checks for collision with the mouse and the button 
	if (m_backButton->checkCollision(m_mousePosition))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
		{
			if (m_backButton->getString() == "MAIN MENU") {
				m_loaded = false;
				m_position = sf::Vector2f(1500.0f, 100.0f);
				*m_currentState = GameState::MainMenu;
			}
			m_pressed = true;
		}
	}
}
/// <summary>
/// renders all the UI 
/// </summary>
/// <param name="window"></param>
void EndGame::render(sf::RenderWindow & window) {


	for (int i = 0; i < m_labels.size(); i++) {
		m_labels[i]->render(window);
	}

	m_backButton->render(window);
}