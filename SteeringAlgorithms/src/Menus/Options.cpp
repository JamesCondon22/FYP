#include "Menus/Options.h"
#include <iostream>

/// <summary>
/// initialises the options screen and assigns 
/// the curent state and starting position for the labels 
/// </summary>
/// <param name="state">The current Game State</param>
/// <param name="font">font for the labels</param>
/// <param name="btnfont">font for the buttons</param>
/// <param name="texture">the button texture </param>
/// <param name="window">the window screen</param>
Options::Options(GameState * state, sf::Font & font, sf::Font & btnfont, sf::Texture & texture, sf::RenderWindow & window):
	m_currentState(state),
	m_font(font),
	m_position(100.0f,50.0f),
	m_texture(texture)
{
	m_window = &window;
	ImGui::SFML::Init(*m_window);

	//creates the labels 
	Label* l1 = new Label(m_font, sf::Vector2f(1800.0f, 50.0f));
	Label* l2 = new Label(m_font, sf::Vector2f(1800.0f, 200.0f));
	Label* l3 = new Label(m_font, sf::Vector2f(1800.0f, 300.0f));
	//pushes labels into vector
	m_labels.push_back(l1);
	m_labels.push_back(l2);
	m_labels.push_back(l3);
	//data explanation labels 
	m_labels[0]->setText("Average Execution Time: This is the average time in which it takes each AI character to complete one full update of \n each steering algorithm.");
	m_labels[1]->setText("Interception Time: This is time taken for the AI character to intercept the scripted AI character.");
	m_labels[2]->setText("Path Length: This the length of the path taken to intercept the scripted AI character.");
	//sets the labels size, color 
	for (int i = 0; i < m_labels.size(); i++) {
		m_labels[i]->setColor(sf::Color::Black);
		m_labels[i]->setOutline(sf::Color::Black, 0.0f);
		m_labels[i]->setSize(40);
	}
	//creates a new button
	button = new Button(sf::Vector2f(2000.0f, 600.0f), 600, 150, m_texture, btnfont, "MAIN MENU");
}

Options::~Options()
{
	std::cout << "destructing License " << std::endl;
}

/// <summary>
/// reads the saved data from a text file and 
/// outputs to the screen 
/// <param name="dt">delta time</param>
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
	//enables to read new data from the text file 
	if (!m_loaded) {
		//m_labels.clear();
		m_file.open("resources/assets/DemoFile.txt");
		
	}

	m_mousePositon = sf::Mouse::getPosition(*m_window);

	//checks the if the menu button is clicked 
	if (button->checkCollision(m_mousePositon)){

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && m_pressed == false) {
			//if the main menu button is clicked GameState is changed to Main menu 
			if (button->getString() == "MAIN MENU") {
				m_loaded = false;
				m_position = sf::Vector2f(100.0f, 50.0f);
				*m_currentState = GameState::MainMenu;
			}
			m_pressed = true;
		}
	}
	
	//reads all the data from the text file 
	while (std::getline(m_file, m_line)) {
		//creates a new label and assigns position
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
	//closes the file 
	m_file.close();
	m_loaded = true;
}

/// <summary>
/// renders all labels and buttons 
/// </summary>
/// <param name="window"></param>
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



