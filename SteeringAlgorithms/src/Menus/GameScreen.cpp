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
	if (!m_keyTexture.loadFromFile("resources/assets/key.png")) {

		std::cout << "texture not loading" << std::endl;
	}
	loadLevel("resources/levels/LevelOne.txt");

	m_savedPositions = m_spawnPositions;

	m_mapSprite.setTexture(m_mapTexture);
	m_mapSprite.setPosition(0, 0);
	m_key = new Key(m_keyTexture);
	m_key->setPosition(getRandomPosition());
	
	m_toolbar.setSize(sf::Vector2f(size.x / 2, size.y));
	m_toolbar.setFillColor(sf::Color::White);
	m_toolbar.setOutlineThickness(5.0f);
	m_toolbar.setOutlineColor(sf::Color::Black);
	m_toolbar.setPosition(2400, 0);

	m_scorePosition = sf::Vector2f(m_toolbar.getPosition().x + 50, m_toolbar.getPosition().y + 50);
	
	initAI();

	m_timeLabel = new Label(m_font, m_tile[40][22]->getPosition());
	m_timeLabel->setColor(sf::Color::Red);
	m_timeLabel->setSize(200);
}


GameScreen::~GameScreen() {
	
}


void GameScreen::update(double dt, sf::Vector2i & mouse)
{
	updateScores();

	int x = mouse.x / 30;
	int y = mouse.y / 30;



	if (!beginTimer) {
		m_clock.restart();
		beginTimer = true;
	}
	if (m_clock.getElapsedTime().asMilliseconds() > 1000 && m_time > 0) {
		m_clock.restart();
		m_time -= 1;
	}

	if (m_time <= 0) {
		m_startGame = true;
	}
	/*if (m_time <= 2) {
		m_ghostAI->updatePlotPoints(dt, m_player->getPos());
		checkSplineNodeCollision(m_ghostAI);
	}*/

	m_timeLabel->setText(std::to_string(m_time));

	/*if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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

	}*/
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
	//{
	//	if (x >= 0 && x < 80 && y >= 0 && y < 60)
	//	{
	//		m_tile[x][y]->setObstacle();
	//	}

	//}
	//if (sf::Mouse::isButtonPressed(sf::Mouse::Middle) && !m_Midpressed)
	//{
	//	if (x >= 0 && x < 80 && y >= 0 && y < 60)
	//	{
	//		Obstacle* obstacle = new Obstacle(50, m_TextureObs, sf::Vector2f(0, 0), true);
	//		obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
	//		obstacle->setPosition(m_tile[x][y]->getPosition());
	//		m_obstacles.push_back(obstacle);
	//		m_tile[x][y]->setCircularObs();
	//	}

	//}
	//if (!sf::Mouse::isButtonPressed(sf::Mouse::Middle))
	//{
	//	m_Midpressed = false;
	//}
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && !m_pressed)
	//{
	//	m_file.open("resources/levels/LevelOne.txt"/*, std::ofstream::app*/);
	//	int count = 0;

	//	for (int i = 0; i < 60; i++) {
	//		for (int j = 0; j < 80; j++) {
	//			if (count >= 80)
	//			{
	//				m_file << std::endl;
	//				count = 0;
	//			}
	//			if (m_tile[j][i]->getState() == NState::Blank)
	//			{
	//				m_file << "0";
	//			}
	//			else if (m_tile[j][i]->getState() == NState::Full)
	//			{
	//				m_file << "1";
	//			}
	//			else if (m_tile[j][i]->getState() == NState::Interest)
	//			{
	//				m_file << "2";
	//			}
	//			else if (m_tile[j][i]->getState() == NState::Circle)
	//			{
	//				m_file << "3";
	//			}
	//			count++;
	//		}
	//	}
	//	m_file.close();
	//	m_pressed = true;
	//}
	//if (!sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	//{
	//	m_pressed = false;
	//}


	int curX = m_player->getPos().x / 30;
	int curY = m_player->getPos().y / 30;

	collision(curX, curY);

	if (m_startGame) {

		m_player->update(dt);
		//m_splineAI->setCurve(m_ghostAI->getCurve());
		//m_splineAI->update(dt, m_player->getPos());
		//checkSplineNodeCollision(m_splineAI);

		for (int i = 0; i < m_enemies.size(); i++) {
			m_enemies[i]->update(dt, m_player->getPos());
			checkNodeCollision(m_enemies[i]);
		}
		if (!m_spawnKey) {
			for (int i = 0; i < m_nodes.size(); i++) {
				if (m_nodes[i]->getAlive()) {
					m_counter++;
				}
			}
		}

		if (m_counter <= 0) {
			m_spawnKey = true;
		}
		m_counter = 0;
	}

	

	if (m_spawnKey) {

		*m_aiStates = BehaviourState::ChaseEntity;

		for (int i = 0; i < m_enemies.size(); i++) {
			m_enemies[i]->setBehaviourState(m_aiStates);
		}
		m_key->setActivated(true);
		m_key->checkCollision(m_player->getPos(), m_player->getRadius());

		if (m_key->getCollision())
		{
			m_gameOver = true;
		}
	}
	
	checkPlayerNodeCollision(m_player->getPos(), m_player->getRadius());

	if (m_key->getActive()) {
		m_key->update(dt);
	}
	
	for (int i = 0; i < m_nodes.size(); i++)
	{
		m_nodes[i]->animateNode();
	}

	for (int i = 0; i < m_labels.size(); i++)
	{
		updateEnemyLabel(m_labels[i]);
		updatePlayerLabel(m_labels[i]);
	}
	
	checkGameOver();
	handleKeys();
}

/// <summary>
/// handles all the key presses in the game
/// </summary>
void GameScreen::handleKeys() {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt) && !m_altPressed) {

		for (int i = 0; i < m_enemies.size(); i++) {

			if (m_enemies[i]->getVisuals()) {
				m_enemies[i]->setVisuals(false);
			}
			else {
				m_enemies[i]->setVisuals(true);
			}
		}

		if (m_player->getVisuals()) {
			m_player->setVisuals(false);
		}
		else {
			m_player->setVisuals(true);
		}
		m_altPressed = true;
	}

	if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LAlt)) {
		m_altPressed = false;
	}
}


/// <summary>
/// 
/// </summary>
/// <param name="x"></param>
/// <param name="y"></param>
void GameScreen::collision(int x, int y)
{

	if (m_tile[x][y - 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y < m_tile[x][y - 1]->getPosition().y + 55)
		{
			m_player->setPosition(sf::Vector2f(m_player->getPos().x, m_tile[x][y - 1]->getPosition().y + 55));
		}
	}
	if (m_tile[x][y + 1]->getState() == NState::Full)
	{
		if (m_player->getPos().y > m_tile[x][y + 1]->getPosition().y - 25)
		{
			m_player->setPosition(sf::Vector2f(m_player->getPos().x, m_tile[x][y + 1]->getPosition().y - 25));
		}
	}

	if (m_tile[x - 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x < m_tile[x - 1][y]->getPosition().x + 55)
		{
			m_player->setPosition(sf::Vector2f(m_tile[x - 1][y]->getPosition().x + 55, m_player->getPos().y));
		}
	}
	if (m_tile[x + 1][y]->getState() == NState::Full)
	{

		if (m_player->getPos().x > m_tile[x + 1][y]->getPosition().x - 25)
		{
			m_player->setPosition(sf::Vector2f(m_tile[x + 1][y]->getPosition().x - 25, m_player->getPos().y));
		}
	}
}

/// <summary>
/// reads from the file and loads the current level
/// initialises the 80 X 60 tile array
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

			if (chars[counter] == '0') {

				m_tile[j][i]->setBlank();
			}
			else if (chars[counter] == '1') {

				m_tile[j][i]->setObstacle();
			}
			else if (chars[counter] == '2') {

				m_tile[j][i]->setInterest();
				GameNode *circ = new GameNode(10, m_textureNode);
				circ->setPosition(sf::Vector2f(0, 0));
				circ->setColor(sf::Color(255, 0, 0));
				circ->setOrigin(circ->getRadius(), circ->getRadius());
				circ->setPosition(sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25));
				m_nodes.push_back(circ);
			}
			else if (chars[counter] == '3') {

				m_tile[j][i]->setCircularObs();
				Obstacle* obstacle = new Obstacle(50, m_TextureObs, sf::Vector2f(0, 0), true);
				obstacle->setPosition(sf::Vector2f(0, 0));
				obstacle->setOrigin(obstacle->getRadius(), obstacle->getRadius());
				obstacle->setPosition(sf::Vector2f(m_tile[j][i]->getPosition().x + 25, m_tile[j][i]->getPosition().y + 25));
				m_obstacles.push_back(obstacle);
			}
			else if (chars[counter] == '4') {

				m_keyPositions.push_back(m_tile[j][i]->getPosition());

			}
			else if (chars[counter] == '5') {
				m_spawnPositions.push_back(m_tile[j][i]->getPosition());
			}

			counter++;
		}
	}
	chars.empty();


}

/// <summary>
/// initialises all the AI and the player
/// sets a score for each AI and player 
/// sets the enemy states to Node chase state
/// </summary>
void GameScreen::initAI() {

	m_player = new Player(m_obstacles);
	//m_splineAI = new CRSplineAI(m_nodes, m_obstacles);
	//m_ghostAI = new CRSplineAI(m_nodes, m_obstacles);

	//m_splineAI->setTag("AI");
	//m_ghostAI->setTag("GHOST");

	m_player->setPosition(initPosition());
	//m_ghostAI->setPosition(initPosition());
	//m_splineAI->setPosition(m_ghostAI->getPos());
	//m_ghostAI->setRadius(10);
	m_player->setVisuals(false);

	initUIText(m_player->getScore(), m_player->getColor());
	//initUIText(m_splineAI->getScore(), m_splineAI->getColor());

	m_scores.push_back(std::make_pair(m_player->getName(), m_player->getScore()));
	//m_scores.push_back(std::make_pair(m_splineAI->getName(), m_splineAI->getScore()));

	Enemy* m_interAi = new InterpolatingAI(m_nodes, m_obstacles);
	Enemy* m_interAiTwo = new InterpolatingTwo(m_nodes, m_obstacles);
	Enemy* m_basicContext = new FrayAI(m_nodes, m_obstacles);
	Enemy* m_dynamAI = new DynamicVectorAI(m_nodes, m_obstacles);
	Enemy* m_efficAI = new EfficiencyAI(m_nodes, m_obstacles);
	Enemy* m_tradAI = new Traditional(m_nodes, m_obstacles);

	m_enemies.push_back(m_interAi);
	m_enemies.push_back(m_interAiTwo);
	m_enemies.push_back(m_basicContext);
	m_enemies.push_back(m_dynamAI);
	m_enemies.push_back(m_efficAI);
	m_enemies.push_back(m_tradAI);

	m_aiStates = new BehaviourState;
	*m_aiStates = BehaviourState::ChaseNode;

	for (int i = 0; i < m_enemies.size(); i++) {

		m_enemies[i]->setPosition(initPosition());
		m_enemies[i]->setBehaviourState(m_aiStates);
		m_scores.push_back(std::make_pair(m_enemies[i]->getName(), m_enemies[i]->getScore()));
		initUIText(m_enemies[i]->getScore(), m_enemies[i]->getColor());
		m_enemies[i]->setVisuals(false);
	}	

	//m_ghostAI->setBehaviourState(m_aiStates);
	//m_splineAI->setBehaviourState(m_aiStates);
}

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="rad"></param>
void GameScreen::checkNodeCollision(Enemy * enemy)
{
	if (Math::circleCollision(m_nodes[enemy->getNodeIndex()]->getPosition(), enemy->getPos(), m_nodes[enemy->getNodeIndex()]->getRadius(), enemy->getRadius()))
	{
		if (m_nodes[enemy->getNodeIndex()]->getAlive()) {

			m_nodes[enemy->getNodeIndex()]->setAlive(false);
			auto score = enemy->getScore();
			score = score + 10;
			enemy->setScore(score);
		}
	}
}

/// <summary>
/// 
/// </summary>
/// <param name="pos"></param>
/// <param name="rad"></param>
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


void GameScreen::checkSplineNodeCollision(CRSplineAI * enemy) {
	
	if (enemy->getTag() == "AI") {
		if (Math::circleCollision(m_nodes[enemy->getClosestNode()]->getPosition(), enemy->getPos(), m_nodes[enemy->getClosestNode()]->getRadius(), enemy->getRadius()))
		{
			if (m_nodes[enemy->getClosestNode()]->getAlive()) {

				m_nodes[enemy->getClosestNode()]->setAlive(false);
				auto score = enemy->getScore();
				score = score + 10;
				enemy->setScore(score);
			}
		}
	}
	else {

		if (Math::circleCollision(m_nodes[enemy->getNodeIndex()]->getPosition(), enemy->getPos(), m_nodes[enemy->getNodeIndex()]->getRadius(), enemy->getRadius()))
		{

			if (m_nodes[enemy->getNodeIndex()]->getAlive() && !m_nodes[enemy->getNodeIndex()]->getCompleted()) {

				m_nodes[enemy->getNodeIndex()]->setCompleted(true);
			}
		}
	}
	
		

			
		
}

/// <summary>
/// 
/// </summary>
void GameScreen::initUIText(int score, sf::Color color)
{
	Label* label = new Label(m_font, m_toolbar.getPosition());
	label->setText("Score: " + std::to_string(score));
	label->setSize(50);
	label->setColor(color);
	label->setPosition(m_scorePosition);
	m_scorePosition.y += 100;
	m_labels.push_back(label);
}


void GameScreen::updateEnemyLabel(Label* label) {

	for (int i = 0; i < m_enemies.size(); i++) {
		
		if (label->getColor() == m_enemies[i]->getColor()) {
			label->setText("Score: " + std::to_string(m_enemies[i]->getScore()));
		}
	}
	/*if (label->getColor() == m_splineAI->getColor()) {
		label->setText("Score: " + std::to_string(m_splineAI->getScore()));
	}*/
}


void GameScreen::updatePlayerLabel(Label* label) {

	if (label->getColor() == m_player->getColor()) {

		label->setText("Score: " + std::to_string(m_player->getScore()));
	}

}


void GameScreen::checkGameOver() {

	if (m_gameOver) {
		saveScores("resources/assets/scores.txt");
		resetGame();
		*m_currentState = GameState::EndGame;
	}
}


/// <summary>
/// resets the player and the AI characters
/// Resets the AI back to their Node chasing state
/// resets all the scores for all the characters
/// resets the key, spawn positions and timer
/// </summary>
void GameScreen::resetGame() {
	
	m_spawnPositions = m_savedPositions;

	m_gameOver = false;
	m_startGame = false;
	m_spawnKey = false;
	beginTimer = false;

	m_key->setActivated(false);
	m_key->setCollision(false);

	m_key->setPosition(getRandomPosition());
	m_player->setPosition(initPosition());
	//m_ghostAI->setPosition(initPosition());
	//m_splineAI->setPosition(m_ghostAI->getPos());

	m_player->setScore(0);
	m_player->reset();
	m_time = 3;

	for (int i = 0; i < m_nodes.size(); i++) {
		m_nodes[i]->setAlive(true);
	}

	m_aiStates = new BehaviourState;
	*m_aiStates = BehaviourState::ChaseNode;

	for (int i = 0; i < m_enemies.size(); i++) {

		m_enemies[i]->setPosition(initPosition());
		m_enemies[i]->setBehaviourState(m_aiStates);
		m_enemies[i]->setVisuals(false);
		m_enemies[i]->resetGame();
		m_enemies[i]->setScore(0);
	}

	//m_splineAI->setBehaviourState(m_aiStates);
	//m_splineAI->setVisuals(false);
	//m_splineAI->resetGame();
	//m_splineAI->setScore(0);

	//m_ghostAI->setBehaviourState(m_aiStates);
	//m_ghostAI->resetGame();
	//m_ghostAI->setVisuals(false);

	for (int i = 0; i < m_scores.size(); i++) {
		m_scores[i].second = 0;
	}
	for (int i = 0; i < m_labels.size(); i++) {
		m_labels[i]->setText("Score: " + std::to_string(0));
	}
	
}


void GameScreen::saveScores(std::string path) {
	m_Scorefile.open(path);

	
	for (int i = 0; i < m_scores.size(); i++) {
		m_Scorefile << i + 1 << ". " << m_scores[i].first << ": " << m_scores[i].second << std::endl;
	}

	m_Scorefile.close();
}

/// <summary>
/// 
/// </summary>
void GameScreen::updateScores()
{
	for (int i = 0; i < m_scores.size(); i++)
	{
		if (m_scores[i].first == m_player->getName()) {
			m_scores[i].second = m_player->getScore();
		}
		
		for (int j = 0; j < m_enemies.size(); j++) {

			if (m_scores[i].first == m_enemies[j]->getName()) {
				m_scores[i].second = m_enemies[j]->getScore();
			}
		}
	} 
	
	std::sort(m_scores.begin(), m_scores.end(), [](const std::pair<std::string, int> &a, const std::pair<std::string, int> &b)
	{
		return (a.second > b.second);
	});

}

/// <summary>
/// get a random position for the key Object 
/// This is called at the end of a level 
/// </summary>
/// <returns></returns>
sf::Vector2f GameScreen::getRandomPosition() {
	int total = m_keyPositions.size();
	int num = std::rand() % total;
	return sf::Vector2f(m_keyPositions[num].x + 25.0f, m_keyPositions[num].y + 25.0f);
}


sf::Vector2f GameScreen::initPosition() {

	sf::Vector2f position;
	int total = m_spawnPositions.size();
	int num = std::rand() % total;
	position = sf::Vector2f(m_spawnPositions[num].x, m_spawnPositions[num].y);

	for (int i = 0; i < m_spawnPositions.size(); i++) {
		auto pos = sf::Vector2f(m_spawnPositions[i].x, m_spawnPositions[i].y);
		if (position == pos) {
			m_spawnPositions.erase(m_spawnPositions.begin() + i);
		}
	}

	return position;
}

/// <summary>
/// 
/// </summary>
/// <param name="window"></param>
void GameScreen::render(sf::RenderWindow & window)
{
	window.draw(m_mapSprite);
	m_player->render(window);

	for (auto &enemy : m_enemies) {
		enemy->render(window);
	}

	//m_splineAI->render(window);
	//m_ghostAI->render(window);

	if (m_key->getActive()) {
		m_key->render(window);
	}
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
	if (!m_startGame) {
		m_timeLabel->render(window);
	}
}