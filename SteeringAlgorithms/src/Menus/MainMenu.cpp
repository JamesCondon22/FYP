#include "Menus/MainMenu.h"
#include <iostream>

MainMenu::MainMenu(GameState * state):
	m_currentState(state)
{
	
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
	
}

