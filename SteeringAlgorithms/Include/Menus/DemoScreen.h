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
#include "../Headers/CRSpline.h"
#include "../Headers/Label.h"
#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>

class DemoScreen
{
public:
	DemoScreen(GameState * state, sf::Font & font);
	~DemoScreen();
	void update(double dt, int active, std::string lastBtnPress);
	void render(sf::RenderWindow& window);
	void checkCollision(TestBot * bot, Enemy * enemy, std::string lastbtnPress);
	void checkSplineCollision(TestBot * bot, CRSplineAI * enemy, std::string lastbtnPress);
	void handleKeys();
	void checkRun(Enemy * enemy, int id);
	void checkRunAll(Enemy * enemy);
	void checkCompare(Enemy * enemy);
	void initAI();

private:
	sf::Window m_window;
	TestBot * m_testBot;

	
	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_circles;
	std::vector<GameNode*> m_nodes;
	std::vector<Enemy*> m_enemies;

	LevelData m_level;
	PathData m_path;

	sf::Texture m_textureObs;
	sf::Texture m_nodeTexture;
	GameState * m_currentState;

	bool m_startDemonstration = false;
	bool m_pressed = false;
	bool m_reset = false;

	sf::Time m_timer;
	sf::Clock m_clock;

	int m_id = 1;
	double m_cumulativeTime;
	double MAX_TIME = 3000.0;
	double GHOST_TIME = 2000.0;
	std::ofstream m_file;
	bool m_runningUpdate = false;
	bool m_runRender = false;

	CRSplineAI* m_ghostAI;
	CRSplineAI* m_splineAI;

	Label* m_aitypeLabel;
	sf::Vector2f m_labelPosition;
	sf::Font m_font;
	BehaviourState * m_aiStates;

	bool m_altPressed = false;
	int m_counter = 0;
	std::vector<sf::RectangleShape> m_bounding;
	std::vector<Label*> m_labels;
	Label* m_timeLabel;
	Label* m_startLabel;
	bool m_startTimer = false;
};
#endif // !