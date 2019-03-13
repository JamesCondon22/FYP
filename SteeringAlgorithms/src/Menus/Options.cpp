#include "Menus/Options.h"
#include <iostream>

Options::Options(GameState * state, sf::Font & font, sf::RenderWindow & window):
	m_currentState(state),
	m_font(font),
	m_position(50,50)
	//m_window(window)
{
	ImGui::SFML::Init(window);
	m_window = &window;
	m_file.open("resources/assets/DemoFile.txt");
}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}


void Options::update(double dt)
{
	ImGui::SFML::Update(*m_window, m_clock.restart());
	//ImGui::ShowTestWindow();
	ImGui::Begin("Hello, world!");
	ImGui::Button("Look at this pretty button");
	ImGui::End();
	ImGui::EndFrame();

	while (std::getline(m_file, m_line))
	{
		std::cout << m_line;
		Label * label = new Label(m_font, m_position);
		label->setText(m_line);
		m_position.y = m_position.y += 50;

		if (m_position.y > 900)
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
	ImGui::SFML::Render(window);
	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[i]->render(window);
	}
}



