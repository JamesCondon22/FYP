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


class InterpolatingAI : public Enemy
{
public:
	InterpolatingAI(std::vector<GameNode*>  path, std::vector<Obstacle*>  obs);
	~InterpolatingAI();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);

	steering seek(sf::Vector2f position);

	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();

	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	void checkDirection();
	void calculation();

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	bool getVisuals() { return m_visuals; }
	bool getCollided() { return m_collided; }
	bool getActive() { return m_active; }
	void setActive(bool active) { m_active = active; }
	void setCollided(bool collide) { m_collided = collide; }
	void setVisuals(bool visuals) { m_visuals = visuals; }

	void generatePath(double dt);
	void handleTimer();
	void setState(GameState state) { m_state = state; }

	double findLargest(std::map<Direction, double> vec);
	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getTime() { return m_currentTime; }
	double getTotalRotation() { return m_totalRotations; }
	double getAverageRotations();
	double getAverageExecTime();

	int getRadius() { return m_radius; }
	int getNodeIndex() { return m_nodeIndex; }
	int getId() { return m_id; }
	int getScore() { return m_score; }
	void setScore(int score) { m_score = score; }
	void setBehaviourState(BehaviourState* state) { m_currentBehaviour = state; }

	sf::Color getColor() { return m_color; }

	void setPosition(sf::Vector2f pos);
	void resetGame();
	void resetDemo();
	void calculateRotations();

	std::string getName() { return "Average Interpolation"; }

private:
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_heading;
	sf::Vector2f curDirection = sf::Vector2f(0, 0);

	steering m_steering;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;

	ContextDecisionMaker mapDecisions;
	sf::CircleShape m_surroundingCircle;
	sf::RectangleShape m_rect;

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	std::vector<double> m_distancesDangerCopy;

	double curLargest = 0;
	double curLargestDanger = 0;
	
	std::vector<Path*> m_pathLine;
	std::vector<GameNode*> m_nodes;
	std::vector<DirectionalLine> m_lineVec;
	std::vector<Obstacle*> m_obstacles;

	int currentObs = 0;
	int currentNode = 0;
	int m_size = 16;
	int m_radius = 30;
	int m_id = 2;
	int m_nodeIndex = 0;
	int m_score = 0;

	bool m_active = false;
	bool m_collided = false;
	bool m_startTimer = false;
	bool m_InGame = false;
	bool m_visuals = true;
	
	float m_speed;
	double MAX_SPEED;
	double m_timeAmount = 0;
	double m_totalPathLength = 0;
	double m_rotation;
	double m_timeEfficiency;
	double m_averageExecTime;
	double m_tickCounter;
	double m_lastUpdate;
	double m_timer;
	double m_currentTime;
	double m_lastRotation;
	double m_totalRotations = 0;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	sf::Clock m_clock;
	sf::Time m_time;
	sf::Color m_color;

	BehaviourState* m_currentBehaviour;
	GameState m_state;

};
