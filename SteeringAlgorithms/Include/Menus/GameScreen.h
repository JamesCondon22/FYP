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

class GameScreen
{
public:
	
	GameScreen(GameState * state, sf::Vector2f & size);
	void update(double dt, sf::Vector2i & mouse);
	void render(sf::RenderWindow & window);
	void collision(int x, int y);

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
	InterpolatingAI* m_ai;
	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_nodes;
	LevelData m_level;
	sf::Texture m_TextureObs;
};

#endif
