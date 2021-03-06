#ifndef DEMOSCREEN
#define DEMOSCREEN	
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include "../Headers/Player.h"
#include "../Headers/AI/FrayAI.h"
#include "../Headers/AI/InterpolatingAI.h"
#include "../Headers/AI/Traditional.h"
#include "../Headers/UI/Obstacle.h"
#include "../Headers/AI/EfficiencyAI.h"
#include "../Headers/AI/InterpolatingTwo.h"
#include "../Headers/LevelLoader.h"
#include "../Headers/AI/DynamicVectorAI.h"
#include "../Headers/AI/Enemy.h"
#include "../Headers/AI/TestBot.h"
#include "../Headers/AI/CRSpline.h"
#include "../Headers/UI/Label.h"
#include <SFML/Graphics.hpp>

#include <fstream>
#include <vector>

class DemoScreen
{
public:
	DemoScreen(GameState * state, sf::Font & font, sf::RenderWindow & window);
	~DemoScreen();
	void update(double dt, int active, std::string lastBtnPress);
	void render(sf::RenderWindow& window);
	void checkCollision(TestBot * bot, Enemy * enemy, std::string lastbtnPress);
	void checkSplineCollision(TestBot * bot, CRSplineAI * enemy, std::string lastbtnPress);
	void handleKeys();
	void checkRun(Enemy * enemy, int id);
	void checkRunAll(Enemy * enemy);
	void checkCompare(Enemy * enemy);
	void updateRun();
	void updateRunAll();
	void updateCompare();
	void initAI();
	void resetDemo();
	void inputAET(double aet);
	void inputInterceptionTime(double time);
	void inputPaths(double path);
	void inputRotations(double rotation);
	void inputAverageRotations(double rotation);

	std::vector<double> getAETimes() { return m_executionTimes; }
	std::vector<double> getInterceptionTimes() { return m_interceptionTimes; }
	std::vector<double> getPathLengths() { return m_pathLengths; }
	std::vector<double> getRotations() { return m_rotations; }
	std::vector<double> getAverageRotations() { return m_averageRotations; }

private:
	BehaviourState * m_aiStates;
	GameState * m_currentState;

	sf::Window m_window;
	
	std::vector<Obstacle*> m_obstacles;
	std::vector<sf::CircleShape> m_circles;
	std::vector<GameNode*> m_nodes;
	std::vector<Enemy*> m_enemies;

	LevelData m_level;
	PathData m_path;

	sf::Texture m_textureObs;
	sf::Texture m_nodeTexture;

	bool m_startDemonstration = false;
	bool m_pressed = false;
	bool m_reset = false;
	bool m_runningUpdate = false;
	bool m_runRender = false;

	sf::Time m_timer;
	sf::Clock m_clock;
	std::ofstream m_file;

	double m_cumulativeTime;
	double MAX_TIME = 1000.0;  // 3
	double GHOST_TIME = 500.0; // 2

	CRSplineAI* m_ghostAI;
	CRSplineAI* m_splineAI;
	TestBot * m_testBot;

	std::vector<sf::RectangleShape> m_bounding;
	std::vector<Label*> m_labels;

	Label* m_timeLabel;
	Label* m_startLabel;
	Label* m_aitypeLabel;
	sf::Vector2f m_labelPosition;
	sf::Font m_font;

	bool m_graphSet = false;
	bool m_altPressed = false;
	bool m_startTimer = false;

	int m_counter = 0;
	int MAX_AI = 7;
	int m_index = 0;
	int m_id = 1;

	std::vector<double> m_executionTimes;
	std::vector<double> m_interceptionTimes;
	std::vector<double> m_pathLengths;
	std::vector<double> m_rotations;
	std::vector<double> m_averageRotations;


};
#endif // !