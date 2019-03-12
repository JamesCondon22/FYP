#include "Menus/Options.h"
#include <iostream>

Options::Options(GameState * state):
	m_currentState(state)
{

}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}


void Options::update(double dt)
{
	
}

void Options::render(sf::RenderWindow & window)
{
	
}



