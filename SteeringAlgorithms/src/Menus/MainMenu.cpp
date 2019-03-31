#include "Menus/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(GameState * state, sf::Font & font) :
	m_currentState(state),
	m_font(font)
{

	m_texture.loadFromFile("resources/assets/button.png");
	initButtons();
}


MainMenu::~MainMenu()
{
	std::cout << "destructing Splash" << std::endl;

}


void MainMenu::update(double dt, sf::Window & window)
{
	m_mousePosition = sf::Mouse::getPosition(window);

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
/// sets pressed to false
/// </summary>
/// <param name="button">the current button being pressed</param>
void MainMenu::handleInputs(Button & button)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
	{
		if (button.getString() == "GAME") {
			*m_currentState = GameState::GameScreen;
		}

		else if (button.getString() == "DEMO") {
			*m_currentState = GameState::Menu;
		}
		m_pressed = true;
	}
}


void MainMenu::render(sf::RenderWindow & window)
{
	window.clear(sf::Color(255, 255, 255));

	for (int i = 0; i < m_buttons.size(); i++)
	{
		m_buttons[i]->render(window);
	}
}


void MainMenu::initButtons()
{
	Button *buttonOne = new Button(sf::Vector2f(700, 200), 400, 150, m_texture, m_font, "DEMO");
	Button *buttonTwo = new Button(sf::Vector2f(700, 400), 400, 150, m_texture, m_font, "GAME");


	m_buttons.push_back(buttonOne);
	m_buttons.push_back(buttonTwo);
}

