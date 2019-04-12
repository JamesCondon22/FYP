#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string.h>
#include "../ContextDecisionMaker.h"
#include "../MathHelper.h"
#include "../UI/Obstacle.h"
#include "../DirectionalLine.h"
#include "Enemy.h"
#include "../UI/Path.h"

class EfficiencyAI : public Enemy
{
public:

	EfficiencyAI(std::vector<GameNode*> path, std::vector<Obstacle*>  obs);
	~EfficiencyAI();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);

	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f normalize(sf::Vector2f vec);

	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	void checkDirection(double dt);
	void calculation();

	steering seek(sf::Vector2f position);

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);
	float mag(sf::Vector2f & v);

	int getId() { return m_id; }
	int getRadius() { return m_radius; }
	int getScore() { return m_score; }
	int getNodeIndex() { return m_nodeIndex; }

	bool getVisuals() { return m_visuals; }
	bool getCollided() { return m_collided; }
	bool getActive() { return m_active; }
	void setActive(bool active) { m_active = active; }
	void setCollided(bool collide) { m_collided = collide; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	
	void generatePath(double dt);
	void handleTimer();
	
	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	double getTime() { return m_currentTime; }
	double getTotalRotation() { return m_totalRotations; }
	double getAverageRotations();

	double findLargest(std::map<Direction, double> vec);

	void setState(GameState state) { m_state = state; }
	void setBehaviourState(BehaviourState *state) { m_currentBehaviour = state; }
	void setScore(int score) { m_score = score; }
	void setPosition(sf::Vector2f pos);
	
	sf::Color getColor() { return m_color; }

	void resetGame();
	void resetDemo();
	void calculateRotations();

	std::string getName() { return "Efficiency AI"; }
private:
	GameState m_state;
	BehaviourState* m_currentBehaviour;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_heading;
	sf::Vector2f UpRadial = sf::Vector2f(0, 0);
	sf::Vector2f curDirection = sf::Vector2f(0, 0);

	steering m_steering;
	
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::CircleShape m_surroundingCircle;
	sf::RectangleShape m_rect;
	
	ContextDecisionMaker mapDecisions;

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	std::vector<sf::Vector2f> m_distVecs;
	std::vector<GameNode*> m_nodes;
	std::vector<DirectionalLine> m_lineVec;
	std::vector<Obstacle*> m_obstacles;

	int m_nodeIndex = 0;
	int currentNode = 0;
	int currentObs = 0;
	int m_size = 16;
	int m_prevId = 0;
	int m_radius = 30;
	int m_id = 4;
	int m_score = 0;

	sf::Time m_timeSinceLastUpdate;
	Direction m_lastDirection;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;

	float m_speed;
	double m_rotation;
	double m_timeSinceLast = 0;
	double MAX_SPEED;
	double MaxDistance = 0;
	double WantedDistance = 0;
	double m_currentDistance = 0;
	double curLargest = 0;
	double curLargestDanger = 0;
	double m_timeAmount = 0;
	double m_totalPathLength = 0;

	bool startTimer = false;
	bool m_begin = false;
	bool m_active = false;
	bool m_collided = false;
	bool m_startTimer = false;
	bool m_visuals = true;

	std::vector<Path*> m_pathLine;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	sf::Color m_color;
	sf::Clock m_clock2;
	sf::Clock m_clock;
	sf::Time m_time;
	
	double m_lastRotation;
	double m_totalRotations = 0;
	double m_timeEfficiency;
	double m_averageExecTime;
	double m_tickCounter;
	double m_lastUpdate;
	double m_timer;
	double m_currentTime;

};
