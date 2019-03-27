#include "Menus/GameScreen.h"


GameScreen::GameScreen(GameState * state, sf::Vector2f & size, sf::Font & font) :
	m_font(font),
	m_currentState(state)
{
	if (!m_TextureObs.loadFromFile("resources/assets/noEntry.png")) {

		std::cout << "texture not loading" << std::endl;
	}
	if (!m_textureNode.loadFromFile("resources/assets/strawberry.png")) {

		std::cout << "texture not loading" << std::endl;
	}
	if (!m_mapTexture.loadFromFile("resources/assets/mapSprite.png")) {

		std::cout << "texture not loading" << std::endl;
	}
	loadLevel("resources/levels/LevelOne.txt");

	/*for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 80; j++) {
			m_tile[j][i] = new Tile(30 * j, 30 * i, j, i);
		}
	}*/

	camera = new Camera(size);
	m_mapSprite.setTexture(m_mapTexture);
	m_mapSprite.setPosition(0, 0);

	m_player = new Player(m_obstacles);
	m_ai = new InterpolatingAI(m_nodes, m_obstacles);
	m_ai->setState(*m_currentState);

	m_toolbar.setSize(sf::Vector2f(size.x / 2, size.y));
	m_toolbar.setFillColor(sf::Color::White);
	m_toolbar.setOutlineThickness(5.0f);
	m_toolbar.setOutlineColor(sf::Color::Black);
	m_toolbar.setPosition(2400, 0);
	initUIText();

	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[0]->setPosition(sf::Vector2f(m_toolbar.getPosition().x + 50, m_toolbar.getPosition().y + 20));
		m_labels[0]->setText("Score: " + std::to_string(m_player->getScore()));

		m_labels[1]->setPosition(sf::Vector2f(m_labels[0]->getPosition().x, m_labels[0]->getPosition().y + 200));
		m_labels[1]->setText("Score: " + std::to_string(m_ai->getScore()));
	}

	m_scores.push_back(std::make_pair(m_player->getName(), m_player->getScore()));
	m_scores.push_back(std::make_pair(m_ai->getName(), m_ai->getScore()));

}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	updateScores();
	//camera->setPosition(m_player->getPos());
	//camera->update();

	int x = mouse.x / 30;
	int y = mouse.y / 30;

	m_player->update(dt);

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (x >= 0 && x < 80 && y >= 0 && y < 60)
		{
			GameNode *circ = new GameNode(10, m_textureNode);
			circ->setPosition(sf::Vector2f(0, 0));
			circ->setColor(sf::Color(255, 0, 0));
			circ->setOrigin(circ->getRadius(), circ->getRadius());
			circ->setPosition(sf::Vector2f(m_tile[x][y]->getPosition().x + 15, m_tile[x][y]->getPosition().y + 15));
			m_nodes.push_back(circ);
			m_tile[x][y]->setInterest();
		}
		
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	{
		if (x >= 0 && x < 80 && y >= 0 && y < 60)
		{
			m_tile[x][y]->setObstacle();
		}

	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !m_Midpressed)
	{
		if (x >= 0 && x < 80 && y >= 0 && y < 60)
		{
			Obstacle* obstacle = new Obstacle(50, m_TextureObs, sf::Vector2f(0, 0), true);
			obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
			obstacle->setPosition(m_tile[x][y]->getPosition());
			m_obstacles.push_back(obstacle);
			m_tile[x][y]->setCircularObs();
		}

	}
	if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	{
		m_Midpressed = false;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_pressed)
	{
		m_file.open("resources/levels/LevelOne.txt"/*, std::ofstream::app*/);
		int count = 0;

		for (int i = 0; i < 60; i++) {
			for (int j = 0; j < 80; j++) {
				if (count >= 80)
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
	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		m_pressed = false;
	}
	
	
	int curX = m_player->getPos().x / 30;
	int curY = m_player->getPos().y / 30;

	collision(curX, curY);

	m_ai->update(dt, m_player->getPos());
	checkNodeCollision(m_ai->getPos(), m_ai->getRadius());
	checkPlayerNodeCollision(m_player->getPos(), m_player->getRadius());


	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->animateNode();
	}

	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[0]->setText("Score: " + std::to_string(m_player->getScore()));
		m_labels[1]->setText("Score: " + std::to_string(m_ai->getScore()));
	}
	
}


void GameScreen::collision(int x, int y)
{

	if (m_tile[x][y - 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y < m_tile[x][y - 1]->getPosition().y + 55)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y - 1]->getPosition().y + 55);
		}
	}
	if (m_tile[x][y + 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y > m_tile[x][y + 1]->getPosition().y - 25)
		{
			m_player->setPosition(m_player->getPos().x, m_tile[x][y + 1]->getPosition().y - 25);
		}
	}

	if (m_tile[x - 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x < m_tile[x - 1][y]->getPosition().x + 55)
		{
			m_player->setPosition(m_tile[x - 1][y]->getPosition().x + 55, m_player->getPos().y);
		}
	}
	if (m_tile[x + 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x > m_tile[x + 1][y]->getPosition().x - 25)
		{
			m_player->setPosition(m_tile[x + 1][y]->getPosition().x - 25, m_player->getPos().y);
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
	for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 80; j++) {
			m_tile[j][i] = new Tile(30 * j, 30 * i, j, i);

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
				GameNode *circ = new GameNode(10, m_textureNode);
				circ->setPosition(sf::Vector2f(0, 0));
				circ->setColor(sf::Color(255, 0, 0));
				circ->setOrigin(circ->getRadius(), circ->getRadius());
				circ->setPosition(sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25));
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


void GameScreen::checkNodeCollision(sf::Vector2f pos, int rad)
{
	if (Math::circleCollision(m_nodes[m_ai->getNodeIndex()]->getPosition(), pos, m_nodes[m_ai->getNodeIndex()]->getRadius(), rad))
	{
		m_nodes[m_ai->getNodeIndex()]->setAlive(false);
		auto score = m_ai->getScore();
		score += 10;
		m_ai->setScore(score);
	}
}


void GameScreen::checkPlayerNodeCollision(sf::Vector2f pos, int rad)
{
	for (int i = 0; i < m_nodes.size(); i++)
	{
		if (m_nodes[i]->getAlive()) {

			if (Math::circleCollision(m_nodes[i]->getPosition(), pos, m_nodes[i]->getRadius(), rad))
			{
				m_nodes[i]->setAlive(false);
				auto score = m_player->getScore();
				score += 10;
				m_player->setScore(score);
			}
		}
	}

}


void GameScreen::initUIText()
{
	Label* labelOne = new Label(m_font, m_toolbar.getPosition());
	labelOne->setText("Score: " + std::to_string(m_player->getScore()));
	labelOne->setSize(50);
	labelOne->setColor(m_player->getColor());

	Label* labelTwo = new Label(m_font, m_toolbar.getPosition());
	labelTwo->setText("Score: " + std::to_string(0));
	labelTwo->setSize(50);
	labelTwo->setColor(m_ai->getColor());

	m_labels.push_back(labelOne);
	m_labels.push_back(labelTwo);
}


void GameScreen::updateScores()
{
	for (int i = 0; i < m_scores.size(); i++)
	{
		if (m_scores[i].first == m_player->getName()) {
			m_scores[i].second = m_player->getScore();
		}
		if (m_scores[i].first == m_ai->getName()) {
			m_scores[i].second = m_ai->getScore();
		}
	} 
	
	std::sort(m_scores.begin(), m_scores.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
	{
		return (a.second > b.second);
	});

}


void GameScreen::render(sf::RenderWindow & window)
{
	
	//camera->render(window);
	/*for (int i = 0; i < 60; i++) {
		for (int j = 0; j < 80; j++) {

			m_tile[j][i]->render(window);
		}
	}*/
	window.draw(m_mapSprite);
	m_player->render(window);
	m_ai->render(window);
	
	for (auto &node : m_nodes)
	{
		node->render(window);
	}

	for (auto &obs : m_obstacles)
	{
		obs->render(window);
	}

	window.draw(m_toolbar);
	for (int i = 0; i < m_labels.size(); i++)
	{
		m_labels[i]->render(window);
	}
	
	
}