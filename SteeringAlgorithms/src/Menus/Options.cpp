#include "Menus/Options.h"
#include <iostream>

Options::Options(GameState * state, sf::Font & font, sf::Font & btnfont, sf::Texture & texture, sf::RenderWindow & window):
	m_currentState(state),
	m_font(font),
	m_position(100.0f,50.0f),
	m_texture(texture)
{
	m_window = &window;
	ImGui::SFML::Init(*m_window);

	Label* l1 = new Label(m_font, sf::Vector2f(1800.0f, 50.0f));
	Label* l2 = new Label(m_font, sf::Vector2f(1800.0f, 200.0f));
	Label* l3 = new Label(m_font, sf::Vector2f(1800.0f, 300.0f));

	m_labels.push_back(l1);
	m_labels.push_back(l2);
	m_labels.push_back(l3);

	m_labels[0]->setText("Average Execution Time: This is the average time in which it takes each AI character to complete one full update of \n each steering algorithm.");
	m_labels[1]->setText("Interception Time: This is time taken for the AI character to intercept the scripted AI character.");
	m_labels[2]->setText("Path Length: This the length of the path taken to intercept the scripted AI character.");

	for (int i = 0; i < m_labels.size(); i++) {
		m_labels[i]->setColor(sf::Color::Black);
		m_labels[i]->setOutline(sf::Color::Black, 0.0f);
		m_labels[i]->setSize(40);
	}

	button = new Button(sf::Vector2f(2000.0f, 600.0f), 600, 150, m_texture, btnfont, "MAIN MENU");
}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}


void Options::update(double dt)
{
	//ImGui::NewFrame();
	/*ImGui::SFML::Update(*m_window, m_clock.restart());
	ImGui::Begin("Hello, world!");
	ImGui::Button("Button one");
	ImGui::Button("Button two");
	ImGui::SetWindowFontScale(2.5f);
	ImGui::End();
	ImGui::EndFrame();*/
	if (!m_loaded) {
		//m_labels.clear();
		m_file.open("resources/assets/DemoFile.txt");
		
	}

	m_mousePositon = sf::Mouse::getPosition(*m_window);

	
	if (button->checkCollision(m_mousePositon))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false)
		{
			if (button->getString() == "MAIN MENU") {
				m_loaded = false;
				m_position = sf::Vector2f(100.0f, 50.0f);
				*m_currentState = GameState::MainMenu;
			}
			m_pressed = true;
		}
	}
	

	while (std::getline(m_file, m_line))
	{
		Label * label = new Label(m_font, m_position);
		label->setSize(40);
		label->setColor(sf::Color::Black);
		label->setOutline(sf::Color::Black, 0.0f);
		label->setText(m_line);
		m_position.y = m_position.y += 50;

		if (m_position.y > 1200)
		{
			m_position.x = m_position.x + 800;
			m_position.y = 50;
		}
		m_labels.push_back(label);
	}
	m_file.close();
	m_loaded = true;
}


void Options::render(sf::RenderWindow & window)
{
	
	//ImGui::SFML::Render(*m_window);
	window.clear(sf::Color(255, 255, 255));

	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[i]->render(window);
	}

	button->render(window);
}



