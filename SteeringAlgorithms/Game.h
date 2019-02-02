#pragma once
#ifndef GAME
#define GAME
#include "Player.h"
#include "FrayAI.h"
#include "Traditional.h"
#include "Obstacle.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include "LevelLoader.h"

/// <summary>
/// @brief Main class for the SFML Playground project.
/// 
/// This will be a single class framework for learning about SFML.
/// </summary>
/// 


class Game
{
public:
	Game();
	void run();
protected:
	void update(double dt);
	void render();
	void processEvents();
	void processGameEvents(sf::Event&);

	void generatePath();
	// main window
	sf::RenderWindow m_window;
	Player* m_player;
	Traditional * m_trad;
	FrayAI * m_ai;
	sf::Texture m_texture;
	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_circles;
	std::vector<sf::CircleShape> m_nodes;
	LevelData m_level;
	PathData m_path;
};

#endif