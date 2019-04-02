#include "Menus/EndGame.h"

EndGame::EndGame(GameState * state, sf::Font & font) :
	m_currentState(state),
	m_position(100.0f,100.0f),
	m_font(font)
{
	m_texture.loadFromFile("resources/assets/button.png");
	m_backButton = new Button(sf::Vector2f(800.0f, 100.0f), 600, 150, m_texture, m_font, "MAIN MENU");
}



void EndGame::update(double dt) {

	if (!m_loaded) {
		m_file.open("resources/assets/scores.txt");
	}

	while (std::getline(m_file, m_line))
	{
		std::cout << m_line << std::endl;
		Label * label = new Label(m_font, m_position);
		label->setText(m_line);
		label->setSize(50);
		m_position.y += 100.0f;
		m_labels.push_back(label);
	}
	m_file.close();
	m_loaded = true;
	

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
	{
		if (m_backButton->getString() == "MAIN MENU") {
			*m_currentState = GameState::MainMenu;
		}
		m_pressed = true;
	}
}

void EndGame::render(sf::RenderWindow & window) {


	for (int i = 0; i < m_labels.size(); i++) {
		m_labels[i]->render(window);
	}

	m_backButton->render(window);
}