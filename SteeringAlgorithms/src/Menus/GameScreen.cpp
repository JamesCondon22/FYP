#include "Menus/GameScreen.h"


GameScreen::GameScreen(GameState * state):
	m_currentState(state)
{
	m_readFile.open("resources/levels/LevelOne.txt");

	

	//char num = "0";
	int x = 0;
	int y = 0;
	std::vector<char> m_chars;

	while (std::getline(m_readFile, m_line))
	{
		for (int i = 0; i < m_line.length(); i++)
		{
			if (m_line.at(i) == '0')
			{
				std::cout << "0" << std::endl;
			}
			if (m_line.at(i) == '1')
			{
				std::cout << "0" << std::endl;
			}
			m_chars.push_back(m_line.at(i));
		}
	}
	m_readFile.close();

	int counter = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			m_tile[j][i] = new Tile(50 * j, 50 * i, j, i);
			if (m_chars[counter] == '0')
			{
				m_tile[j][i]->setBlank();
			}
			else
			{
				m_tile[j][i]->setObstacle();
			}
			counter++;
		}
	}

	
}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	
	int x = mouse.x / 50;
	int y = mouse.y / 50;

	std::cout << x << ", " << y << std::endl;
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (x >= 0 && x < 50 && y >= 0 && y < 50)
		{
			m_tile[x][y]->setObstacle();
		}
		
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (x >= 0 && x < 50 && y >= 0 && y < 50)
		{
			m_tile[x][y]->setBlank();
		}

	}
	
	/*if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_pressed)
	{
		int count = 0;

		for (int i = 0; i < 25; i++) {
			for (int j = 0; j < 50; j++) {
				if (count >= 50)
				{
					m_file << std::endl;
					count = 0;
				}
				if (m_tile[j][i]->getState() == NState::Blank)
				{
					m_file << "0";
				}
				else if (m_tile[j][i]->getState() == NState::Full)
				{
					m_file << "1";
				}
				count++;
			}
		}
		m_file.close();
		m_pressed = true;
	}*/
	
	
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//m_pressed = false;
	}
}


void GameScreen::render(sf::RenderWindow & window)
{
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {

			m_tile[j][i]->render(window);
		}
	}
}