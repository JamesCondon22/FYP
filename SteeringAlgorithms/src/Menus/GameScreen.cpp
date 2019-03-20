#include "Menus/GameScreen.h"


GameScreen::GameScreen(GameState * state, sf::Vector2f & size):
	m_currentState(state)
{
	if (!m_TextureObs.loadFromFile("resources/assets/obstacle.png")) {

		std::cout << "texture not loading" << std::endl;
	}

	loadLevel("resources/levels/LevelOne.txt");

	camera = new Camera(size);

	m_player = new Player();
	m_ai = new InterpolatingAI(m_nodes, m_obstacles);
}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	camera->setPosition(m_player->getPos());
	camera->update();

	int x = mouse.x / 50;
	int y = mouse.y / 50;

	m_player->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (x >= 0 && x < 50 && y >= 0 && y < 50)
		{
			m_tile[x][y]->setInterest();
		}
		
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (x >= 0 && x < 50 && y >= 0 && y < 50)
		{
			m_tile[x][y]->setBlank();
		}

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !m_Midpressed)
	{
		if (x >= 0 && x < 50 && y >= 0 && y < 50)
		{
			Obstacle* obstacle = new Obstacle(50, m_TextureObs, sf::Vector2f(0, 0), true);
			obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
			obstacle->setPosition(m_tile[x][y]->getPosition());
			m_obstacles.push_back(obstacle);
			m_tile[x][y]->setCircularObs();
		}

	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !m_Midpressed)
	{
		m_Midpressed = false;
	}
	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_pressed)
	{
		m_file.open("resources/levels/LevelOne.txt"/*, std::ofstream::app*/);
		int count = 0;

		for (int i = 0; i < 50; i++) {
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
				else if (m_tile[j][i]->getState() == NState::Interest)
				{
					m_file << "2";
				}
				else if (m_tile[j][i]->getState() == NState::Circle)
				{
					m_file << "3";
				}
				count++;
			}
		}
		m_file.close();
		m_pressed = true;
	}
	
	int curX = m_player->getPos().x / 50;
	int curY = m_player->getPos().y / 50;

	collision(curX, curY);

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pressed = false;
	}
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


/// <summary>
/// reads from the file and loads the current level
/// initialises the 50 X 50 tile array
/// sets the positions of the blank, interest and Obstacles and 
/// circular obstacles
/// </summary>
/// <param name="level">the current level</param>
void GameScreen::loadLevel(std::string level)
{
	m_readFile.open(level);

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
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {
			m_tile[j][i] = new Tile(50 * j, 50 * i, j, i);

			if (chars[counter] == '0')
			{
				m_tile[j][i]->setBlank();
			}
			else if (chars[counter] == '1')
			{
				m_tile[j][i]->setObstacle();
			}
			else if (chars[counter] == '2')
			{
				m_tile[j][i]->setInterest();
				sf::CircleShape circ = sf::CircleShape(5);
				circ.setPosition(0, 0);
				circ.setFillColor(sf::Color(255, 0, 0));
				circ.setOrigin(circ.getRadius(), circ.getRadius());
				circ.setPosition(sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25));
				m_nodes.push_back(circ);
			}
			else if (chars[counter] == '3')
			{
				m_tile[j][i]->setCircularObs();
				Obstacle* obstacle = new Obstacle(50, m_TextureObs, sf::Vector2f(0, 0), true);
				obstacle->setPosition(sf::Vector2f(0, 0));
				obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
				obstacle->setPosition(sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25));
				m_obstacles.push_back(obstacle);
			}

			counter++;
		}
	}
	chars.empty();
}


void GameScreen::render(sf::RenderWindow & window)
{
	
	
	for (int i = 0; i < 50; i++) {
		for (int j = 0; j < 50; j++) {

			m_tile[j][i]->render(window);
		}
	}
	
	camera->render(window);
	m_player->render(window);
	m_ai->render(window);
	
	for (auto &node : m_nodes)
	{
		window.draw(node);
	}

	for (auto &obs : m_obstacles)
	{
		obs->render(window);
	}

}