#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN	
#include <SFML/Graphics.hpp>
#include "Menus/State.h"
#include "Headers/Tile.h"
#include "../Headers/Player.h"
#include "Headers/Camera.h"
#include "Headers/InterpolatingAI.h"
#include "Headers/InterpolatingTwo.h"
#include "Headers/FrayAI.h"
#include "Headers/DynamicVectorAI.h"
#include "Headers/EfficiencyAI.h"
#include "Headers/CRSpline.h"
#include "Headers/Traditional.h"
#include "Headers/LevelLoader.h"
#include "Headers/GameNode.h"
#include "Headers/Label.h"
#include "Headers/Key.h"
#include "Headers/Lifebar.h"

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
	sf::Vector2f initPosition();
	sf::Vector2f getRandomPosition();
	std::vector<std::pair<std::string, int>> getScores() { return m_scores; }
	void initAI();
	void handleKeys();
	void resetGame();
private:

	GameState * m_currentState;

	Tile *m_tile[80][60];
	
	sf::Texture m_texture;
	std::ifstream m_readFile;
	std::ofstream m_file;
	std::string m_line = "";
	bool m_pressed;
	bool m_Midpressed;
	Player* m_player;

	Camera * camera;
	Camera * miniMap;

	std::vector<Enemy*> m_enemies;
	CRSplineAI * m_ghostAI;
	CRSplineAI * m_splineAI;
	std::vector<Obstacle*> m_obstacles;
	std::vector<GameNode*> m_nodes;
	LevelData m_level;
	sf::Texture m_TextureObs;
	sf::Texture m_textureNode;
	sf::Texture m_mapTexture;
	sf::Sprite m_mapSprite;
	sf::Texture m_keyTexture;

	sf::Font m_font;
	sf::RectangleShape m_toolbar;

	Label* m_label;
	LifeBar * m_lifebar;
	std::vector<std::pair<std::string, int>> m_scores;

	std::vector<Label*> m_labels;

	int m_tallyScore = 0;
	int m_maxScore = 0;

	BehaviourState * m_aiStates;
	std::vector<sf::Vector2f> m_placePositions;
	Key* m_key;
	std::vector<sf::Vector2f> m_keyPositions;
	std::vector<sf::Vector2f> m_spawnPositions;
	std::vector<sf::Vector2f> m_savedPositions;

	sf::Vector2f m_scorePosition;
	bool m_gameOver = false;
	std::ofstream m_Scorefile;
	sf::Clock m_clock;
	int m_time = 3;

	bool beginTimer = false;
	Label * m_timeLabel;

	bool m_startGame = false;
	bool m_spawnKey = false;

	int m_counter = 0;

	bool m_altPressed = false;

	Label* m_playerLabel;
};

#endif
