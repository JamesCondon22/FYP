#include "Menus/Menu.h"
#include <iostream>

Menu::Menu(GameState * state, sf::Font & font):
	m_currentState(state),
	m_font(font)
{

	m_texture.loadFromFile("resources/assets/button.png");
	initButtons();
}


Menu::~Menu()
{
	std::cout << "destructing Splash" << std::endl;
	
}


void Menu::update(double dt, sf::Window & window)
{
	m_mousePosition = sf::Mouse::getPosition(window);


	if (!m_reset) {
		m_activatedAI = 0;
		resetButtons();
		m_reset = true;
	}
	for (int i = 0; i < m_buttons.size(); i++)
	{
		if (m_buttons[i]->checkCollision(m_mousePosition))
		{
			handleInputs(*m_buttons[i]);
		}
	}
}

/// <summary>
/// checks if the mouse button is pressed
/// sets pressed to false as to check only once
/// </summary>
/// <param name="button">the current button being pressed</param>
void Menu::handleInputs(Button & button)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
	{

		if (button.getString() == "RUN")
		{
			if (m_activatedAI != 0)
			{
				m_lastPressed = "RUN";
				m_reset = false;
				*m_currentState = GameState::Demo;
			}
		}
		if (button.getString() == "RUN ALL")
		{
			m_activatedAI = atoi("1");
			m_lastPressed = "RUN ALL";
			*m_currentState = GameState::Demo;
		}
		if (button.getString() == "COMPARE")
		{
			m_activatedAI = atoi("1");
			m_lastPressed = "COMPARE";
			*m_currentState = GameState::Demo;
		}
		if (button.getString() == "1")
		{
			m_activatedAI = atoi("1");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "2")
		{
			m_activatedAI = atoi("2");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "3")
		{
			m_activatedAI = atoi("3");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "4")
		{
			m_activatedAI = atoi("4");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "5")
		{
			m_activatedAI = atoi("5");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "6")
		{
			m_activatedAI = atoi("6");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}
		if (button.getString() == "7")
		{
			m_activatedAI = atoi("7");
			setLast();
			button.setPressed(true);
			m_lastButton = &button;
			button.update();
		}

		m_pressed = true;
	}
}


void Menu::resetButtons() {
	for (int i = 0; i < m_buttons.size(); i++) {
		m_buttons[i]->setPressed(false);
	}
}


void Menu::setLast() {
	
	for (int i = 0; i < m_buttons.size(); i++) {
		if (m_lastButton != nullptr) {
			if (m_buttons[i]->getString() == m_lastButton->getString()) {
				m_buttons[i]->setPressed(false);
				m_buttons[i]->update();
			}
		}
	}
}
 

void Menu::checkButtons(std::string name)
{

}


void Menu::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->render(window);
	}
}


void Menu::initButtons()
{
	Button *buttonOne = new Button(sf::Vector2f(1500, 1650), 600, 150, m_texture, m_font, "RUN");
	Button *buttonRunAll = new Button(sf::Vector2f(1500, 800), 600, 150, m_texture, m_font, "RUN ALL");
	Button *buttonCompare = new Button(sf::Vector2f(1500, 300), 600, 150, m_texture, m_font, "COMPARE");

	Button *aiButtonOne = new Button(sf::Vector2f(1120, 1450), 150, 150, m_texture, m_font, "1");
	Button *aiButtonTwo = new Button(sf::Vector2f(1320, 1450), 150, 150, m_texture, m_font, "2");
	Button *aiButtonThree = new Button(sf::Vector2f(1520, 1450), 150, 150, m_texture, m_font, "3");
	Button *aiButtonFour = new Button(sf::Vector2f(1720, 1450), 150, 150, m_texture, m_font, "4");
	Button *aiButtonFive = new Button(sf::Vector2f(1920, 1450), 150, 150, m_texture, m_font, "5");
	Button *aiButtonSix = new Button(sf::Vector2f(2120, 1450), 150, 150, m_texture, m_font, "6");
	Button *aiButtonSeven = new Button(sf::Vector2f(2320, 1450), 150, 150, m_texture, m_font, "7");
	
	m_buttons.push_back(buttonOne);
	m_buttons.push_back(buttonRunAll);
	m_buttons.push_back(aiButtonOne);
	m_buttons.push_back(aiButtonTwo);
	m_buttons.push_back(aiButtonThree);
	m_buttons.push_back(aiButtonFour);
	m_buttons.push_back(aiButtonFive);
	m_buttons.push_back(aiButtonSix);
	m_buttons.push_back(aiButtonSeven);
	m_buttons.push_back(buttonCompare);
}

