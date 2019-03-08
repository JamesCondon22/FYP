#include "Menus/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(GameState * state):
	m_currentState(state)
{
	m_texture.loadFromFile("resources/assets/button.png");
	m_font.loadFromFile("resources/assets/bernhc.TTF");
	initButtons();
}


MainMenu::~MainMenu()
{
	std::cout << "destructing Splash" << std::endl;
	
}


void MainMenu::update(double dt)
{
	
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
	Button *buttonOne = new Button(sf::Vector2f(700, 600), 400, 150, m_texture, m_font, "RUN");
	
	Button *aiButtonOne = new Button(sf::Vector2f(50, 300), 150, 150, m_texture, m_font, "1");
	Button *aiButtonTwo = new Button(sf::Vector2f(250, 300), 150, 150, m_texture, m_font, "2");
	Button *aiButtonThree = new Button(sf::Vector2f(450, 300), 150, 150, m_texture, m_font, "3");
	Button *aiButtonFour = new Button(sf::Vector2f(650, 300), 150, 150, m_texture, m_font, "4");
	Button *aiButtonFive = new Button(sf::Vector2f(850, 300), 150, 150, m_texture, m_font, "5");
	Button *aiButtonSix = new Button(sf::Vector2f(1050, 300), 150, 150, m_texture, m_font, "6");

	m_buttons.push_back(buttonOne);
	m_buttons.push_back(aiButtonOne);
	m_buttons.push_back(aiButtonTwo);
	m_buttons.push_back(aiButtonThree);
	m_buttons.push_back(aiButtonFour);
	m_buttons.push_back(aiButtonFive);
	m_buttons.push_back(aiButtonSix);
}

