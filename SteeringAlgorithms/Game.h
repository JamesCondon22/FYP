#pragma once
#ifndef GAME
#define GAME
#include "Player.h"
#include "FrayAI.h"
#include "Traditional.h"
#include "Obstacle.h"
#include <vector>
#include <SFML/Graphics.hpp>

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

	// main window
	sf::RenderWindow m_window;
	Player* m_player;
	Traditional * m_trad;
	FrayAI * m_ai;

	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_circles;
};

#endif