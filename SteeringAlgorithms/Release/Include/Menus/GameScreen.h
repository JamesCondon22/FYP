#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN	
#include <SFML/Graphics.hpp>
#include "Menus/State.h"
#include "Headers/UI/Tile.h"
#include "../Headers/Player.h"
#include "Headers/Camera.h"
#include "Headers/AI/InterpolatingAI.h"
#include "Headers/AI/InterpolatingTwo.h"
#include "Headers/AI/FrayAI.h"
#include "Headers/AI/DynamicVectorAI.h"
#include "Headers/AI/EfficiencyAI.h"
#include "Headers/AI/CRSpline.h"
#include "Headers/AI/Traditional.h"
#include "Headers/LevelLoader.h"
#include "Headers/UI/GameNode.h"
#include "Headers/UI/Label.h"
#include "Headers/UI/Key.h"
#include "Headers/UI/Lifebar.h"

class GameScreen
{
public:
	
	GameScreen(GameState * state, sf::Vector2f & size, sf::Font & font, sf::RenderWindow & window);
	~GameScreen();
	void update(double dt, sf::Vector2i & mouse);
	void render(sf::RenderWindow & window);
	void collision(int x, int y);
	void loadLevel(std::string level);
	void checkNodeCollision(Enemy * enemy);
	void checkPlayerEnemyCollision(Enemy * enemy, Player * player);
	void checkPlayerNodeCollision(sf::Vector2f pos, int rad);
	void checkSplineNodeCollision(CRSplineAI * enemy);
	void checkGameOver();
	void initUIText(int score, sf::Color color);
	void updateScores();
	void updateEnemyLabel(Label * label);
	void updatePlayerLabel(Label * label);
	void saveScores(std::string path);
	void initAI();
	void loadTextures();
	void initLabels();
	void handleKeys();
	void resetGame();
	void checkNodes();

	sf::Vector2f initPosition();
	sf::Vector2f getRandomPosition();

	std::vector<std::pair<std::string, int>> getScores() { return m_scores; }

	
private:

	BehaviourState * m_aiStates;
	GameState * m_currentState;

	Tile *m_tile[80][60];
	
	sf::Texture m_texture;
	sf::Vector2f m_scorePosition;

	std::ifstream m_readFile;
	std::ofstream m_file;
	std::string m_line = "";

	CRSplineAI * m_ghostAI;
	CRSplineAI * m_splineAI;
	Player* m_player;

	std::vector<Enemy*> m_enemies;
	std::vector<Obstacle*> m_obstacles;
	std::vector<GameNode*> m_nodes;

	sf::Texture m_TextureObs;
	sf::Texture m_textureNode;
	sf::Texture m_mapTexture;
	sf::Texture m_keyTexture;

	sf::Sprite m_mapSprite;
	sf::Font m_font;
	sf::RectangleShape m_toolbar;

	Label* m_playerLabel;
	Label * m_timeLabel;
	Label* m_label;
	LifeBar * m_lifebar;
	Key* m_key;

	int m_tallyScore = 0;
	int m_maxScore = 0;
	int m_time = 3;
	int m_counter = 0;

	std::vector<std::pair<std::string, int>> m_scores;
	std::vector<Label*> m_labels;
	std::vector<sf::Vector2f> m_placePositions;
	std::vector<sf::Vector2f> m_keyPositions;
	std::vector<sf::Vector2f> m_spawnPositions;
	std::vector<sf::Vector2f> m_savedPositions;

	std::ofstream m_Scorefile;
	sf::Clock m_clock;

	bool m_startGame = false;
	bool m_spawnKey = false;
	bool m_pressed;
	bool m_Midpressed;
	bool beginTimer = false;
	bool m_gameOver = false;
	bool m_altPressed = false;

};

#endif
