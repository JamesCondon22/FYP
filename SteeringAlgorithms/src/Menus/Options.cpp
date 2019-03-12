#include "Menus/Options.h"
#include <iostream>

Options::Options(GameState * state, sf::Font & font):
	m_currentState(state),
	m_font(font),
	m_position(50,50)
{

	m_file.open("resources/assets/DemoFile.txt");
}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}


void Options::update(double dt)
{
	while (std::getline(m_file, m_line))
	{
		std::cout << m_line;
		Label * label = new Label(m_font, m_position);
		label->setText(m_line);
		m_position.y = m_position.y += 50;
		if (m_position.y > 800)
		{
			m_position.x = m_position.x + 600;
			m_position.y = 50;
		}

		m_labels.push_back(label);
	}

	m_file.close();
	
}

void Options::render(sf::RenderWindow & window)
{
	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[i]->render(window);
	}
}



