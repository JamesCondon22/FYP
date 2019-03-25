#pragma once
#ifndef GAMESCREEN
#define GAMESCREEN	
#include <SFML/Graphics.hpp>
#include "Menus/State.h"
#include "Headers/Tile.h"
#include "../Headers/Player.h"
#include "Headers/Camera.h"
#include "Headers/InterpolatingAI.h"
#include "Headers/LevelLoader.h"
#include "Headers/GameNode.h"

class GameScreen
{
public:
	
	GameScreen(GameState * state, sf::Vector2f & size);
	void update(double dt, sf::Vector2i & mouse);
	void render(sf::RenderWindow & window);
	void collision(int x, int y);
	void loadLevel(std::string level);
	void checkNodeCollision(sf::Vector2f pos, int rad);
	void checkPlayerNodeCollision(sf::Vector2f pos, int rad);
private:

	GameState * m_currentState;

	Tile *m_tile[50][50];
	
	sf::Texture m_texture;
	std::ifstream m_readFile;
	std::ofstream m_file;
	std::string m_line = "";
	bool m_pressed;
	bool m_Midpressed;
	Player* m_player;

	Camera * camera;
	Camera * miniMap;
	InterpolatingAI* m_ai;
	std::vector<Obstacle*> m_obstacles;
	std::vector<GameNode*> m_nodes;
	LevelData m_level;
	sf::Texture m_TextureObs;
	sf::Texture m_textureNode;
	sf::Texture m_mapTexture;
	sf::Sprite m_mapSprite;
};

#endif
