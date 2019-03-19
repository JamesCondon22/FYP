#include "Menus/GameScreen.h"


GameScreen::GameScreen(GameState * state, sf::Vector2f & size):
	m_currentState(state)
{

	m_player = new Player();
	m_readFile.open("resources/levels/LevelOne.txt");
	
	int currentLevel = 1;

	if (!LevelLoader::load(currentLevel, m_level)) {
		return;
	}

	for (PathData const &path : m_level.m_paths) {
		sf::CircleShape circle(10);
		circle.setOrigin(circle.getRadius(), circle.getRadius());
		circle.setPosition(path.m_position);
		circle.setFillColor(sf::Color::Red);
		m_nodes.push_back(circle);
	}

	std::vector<char> chars;

	while (std::getline(m_readFile, m_line))
	{
		for (int i = 0; i < m_line.length(); i++)
		{
			chars.push_back(m_line.at(i));
		}
	}
	m_readFile.close();
	sf::Texture text;
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
				Obstacle *circle = new Obstacle(0, text, sf::Vector2f(50.0f, 50.0f), false);
				circle->setPosition(sf::Vector2f(0.0f, 0.0f));
				circle->setOrigin(25, 25);
				sf::Vector2f pos = sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25);
				circle->setPosition(pos);
				m_obstacles.push_back(circle);
				
			}
			counter++;
		}
	}
	chars.empty();
	camera = new Camera(size);
	
	m_ai = new InterpolatingAI(m_nodes, m_obstacles, true);
}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	camera->setPosition(m_player->getPos());
	camera->update();

	int x = mouse.x / 50;
	int y = mouse.y / 50;

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

	}*/
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

	//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	//m_pressed = false;
	//}
	m_ai->update(dt, m_player->getPos());
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
	camera->render(window);
	m_player->render(window);
	m_ai->render(window);
	
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles[i]->render(window);
		m_obstacles[i]->setColor(sf::Color::Black);
	}
}