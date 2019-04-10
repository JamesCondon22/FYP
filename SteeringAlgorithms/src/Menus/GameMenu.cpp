#include "Menus/GameMenu.h"


GameMenu::GameMenu(GameState * state, sf::Font & btnfont, sf::Font & font) :
	m_currentState(state),
	m_font(btnfont),
	m_fontTwo(font),
	m_position(2000.0f, 50.0f)
{
	m_file.open("resources/assets/help.txt");
	m_texture.loadFromFile("resources/assets/button.png");
	initButtons();

	
}


GameMenu::~GameMenu()
{
	std::cout << "destructing Splash" << std::endl;

}


void GameMenu::update(double dt, sf::Window & window)
{
	m_mousePosition = sf::Mouse::getPosition(window);

	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->checkCollision(m_mousePosition))
		{
			handleInputs(*m_buttons[i]);
		}
	}

	loadData();
}

/// <summary>
/// checks if the mouse button is pressed
/// sets pressed to false
/// </summary>
/// <param name="button">the current button being pressed</param>
void GameMenu::handleInputs(Button & button)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
	{
		if (button.getString() == "LEVEL ONE") {
			*m_currentState = GameState::GameScreen;
		}
		if (button.getString() == "HELP" && !m_renderText) {
			m_renderText = true;
		}
		else if (button.getString() == "HELP" && m_renderText) {
			m_renderText = false;
		}
		m_pressed = true;
	}
}


void GameMenu::render(sf::RenderWindow & window)
{

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->render(window);
	}
	if (m_renderText) {

		for (int i = 0; i < m_labels.size(); i++)
		{
			m_labels[i]->render(window);
		}
	}
}


void GameMenu::initButtons()
{
	Button *buttonOne = new Button(sf::Vector2f(700, 400), 600, 150, m_texture, m_fontTwo, "LEVEL ONE");
	Button *buttonTwo = new Button(sf::Vector2f(700, 800), 600, 150, m_texture, m_fontTwo, "HELP");

	
	m_buttons.push_back(buttonOne);
	m_buttons.push_back(buttonTwo);


}


/// <summary>
/// reads all the data from the text file.
/// positions all the data to the screen.
/// </summary>
void GameMenu::loadData() {
	while (std::getline(m_file, m_line)) {
		//creates a new label and assigns position
		Label * label = new Label(m_fontTwo, m_position);
		label->setSize(50);
		label->setColor(sf::Color::White);
		label->setOutline(sf::Color::Black, 5.0f);
		label->setText(m_line);
		m_position.y = m_position.y += 50;

		m_labels.push_back(label);
	}
	//closes the file 
	m_file.close();
}
