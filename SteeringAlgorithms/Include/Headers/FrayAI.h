#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "ContextDecisionMaker.h"
#include "MathHelper.h"
#include "Obstacle.h"
#include "DirectionalLine.h"
#include "Enemy.h"
#include "Path.h"

class FrayAI : public Enemy
{
public:
	FrayAI(std::vector<GameNode*> path, std::vector<Obstacle*>  obs);
	~FrayAI();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();
	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	sf::Vector2f normalize(sf::Vector2f vec);
	void checkDirection();
	steering seek(sf::Vector2f position);
	void calculation();
	float mag(sf::Vector2f & v);

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);
	sf::RectangleShape m_rect;
	sf::Vector2f getPos();
	double findLargest(std::map<Direction, double> vec);

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	bool compareKeys(std::map<Direction, sf::Vector2f> vec);

	int getId() { return m_id; }

	bool getActive() { return m_active; }
	void setActive(bool active) { m_active = active; }
	void setCollided(bool collide) { m_collided = collide; }

	void generatePath(double dt);
	void handleTimer();

	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	double getTimeEfficiency();
	void setState(GameState state) { m_state = state; }
	std::string getName() { return "Basic Context Maps"; }
	void setBehaviourState(BehaviourState *state) { m_currentBehaviour = state; }
	sf::Color getColor() { return m_color; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	bool getVisuals() { return m_visuals; }
private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	steering m_steering;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	int size;
	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	double m_rotation;
	float m_speed;
	double MAX_SPEED;
	sf::Vector2f m_heading;
	ContextDecisionMaker mapDecisions;
	sf::CircleShape m_surroundingCircle;

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	std::vector<double> m_distancesDangerCopy;

	double curLargest = 0;
	double curLargestDanger = 0;
	sf::Vector2f curDirection = sf::Vector2f(0, 0);
	int m_radius = 30;

	std::vector<GameNode*> m_nodes;
	int currentNode = 0;

	std::vector<Obstacle*> m_obstacles;
	int currentObs = 0;

	int m_size = 16;
	std::vector<DirectionalLine> m_lineVec;

	int m_id = 1;

	bool m_active = false;
	bool m_collided = false;

	std::vector<Path*> m_pathLine;

	double m_timeAmount = 0;
	double m_totalPathLength = 0;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	sf::Clock m_clock2;
	sf::Clock m_clock;
	double m_currentTime;
	sf::Time m_time;

	bool m_startTimer = false;

	double m_timeEfficiency;
	double m_averageExecTime;
	double m_tickCounter;
	double m_lastUpdate;
	double m_timer;

	sf::Color m_color;

	GameState m_state;
	BehaviourState* m_currentBehaviour;

	bool m_visuals = true;
};
