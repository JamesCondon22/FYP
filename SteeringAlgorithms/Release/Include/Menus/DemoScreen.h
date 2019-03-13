#ifndef DEMOSCREEN
#define DEMOSCREEN	
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include "../Headers/Player.h"
#include "../Headers/FrayAI.h"
#include "../Headers/InterpolatingAI.h"
#include "../Headers/Traditional.h"
#include "../Headers/Obstacle.h"
#include "../Headers/EfficiencyAI.h"
#include "../Headers/InterpolatingTwo.h"
#include "../Headers/LevelLoader.h"
#include "../Headers/DynamicVectorAI.h"
#include "../Headers/Enemy.h"
#include "../Headers/TestBot.h"

#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>

class DemoScreen
{
public:
	DemoScreen(GameState * state);
	~DemoScreen();
	void update(double dt, int active);
	void render(sf::RenderWindow& window);
	void checkCollision(TestBot * bot, Enemy * enemy);

private:
	sf::Window m_window;

	Player* m_player;
	Traditional * m_trad;
	TestBot * m_testBot;

	
	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_circles;
	std::vector<sf::CircleShape> m_nodes;
	std::vector<Enemy*> m_enemies;

	LevelData m_level;
	PathData m_path;

	sf::Texture m_textureObs;

	GameState * m_currentState;

	bool m_startDemonstration = false;
	bool m_pressed = false;

	sf::Time m_timer;
	sf::Clock m_clock;

	double m_cumulativeTime;

	double MAX_TIME = 3000.0;

	std::ofstream m_file;
};
#endif // !