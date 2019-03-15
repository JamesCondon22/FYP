#include "Menus/GameScreen.h"


GameScreen::GameScreen(GameState * state):
	m_currentState(state)
{

	m_player = new Player();
	m_readFile.open("resources/levels/LevelOne.txt");
	
	std::vector<char> chars;

	while (std::getline(m_readFile, m_line))
	{
		for (int i = 0; i < m_line.length(); i++)
		{
			chars.push_back(m_line.at(i));
		}
	}
	m_readFile.close();

	int counter = 0;
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {
			m_tile[j][i] = new Tile(50 * j, 50 * i, j, i);
			
			if (chars[counter] == '0')
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
	chars.empty();
	
}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	
	int x = mouse.x / 50;
	int y = mouse.y / 50;

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
	m_player->update(dt);
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
	
	int curX = m_player->getPos().x / 50;
	int curY = m_player->getPos().y / 50;

	collision(curX, curY);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		//m_pressed = false;
	}
}


void GameScreen::collision(int x, int y)
{

	if (m_tile[x][y - 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y < m_tile[x][y - 1]->getPosition().y + 75)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y - 1]->getPosition().y + 75);
		}

	}
	if (m_tile[x][y + 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y > m_tile[x][y + 1]->getPosition().y - 30)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y + 1]->getPosition().y - 30);
		}
	}

	if (m_tile[x - 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x < m_tile[x - 1][y]->getPosition().x + 75)
		{
			m_player->setPosition(m_tile[x - 1][y]->getPosition().x + 75, m_player->getPos().y);
		}
	}
	if (m_tile[x + 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x > m_tile[x + 1][y]->getPosition().x - 30)
		{
			m_player->setPosition(m_tile[x + 1][y]->getPosition().x - 30, m_player->getPos().y);
		}
	}
}


void GameScreen::render(sf::RenderWindow & window)
{

	
	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 50; j++) {

			m_tile[j][i]->render(window);
		}
	}
	m_player->render(window);
}