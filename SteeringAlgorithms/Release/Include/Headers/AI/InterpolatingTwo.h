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

class InterpolatingTwo : public Enemy
{
public:
	InterpolatingTwo(std::vector<GameNode*> path, std::vector<Obstacle*>  obs);
	~InterpolatingTwo();
	void update(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);

	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();

	steering seek(sf::Vector2f position);

	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	void checkDirection();
	void calculation();

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);
	

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	bool getCollided() { return m_collided; }
	bool getVisuals() { return m_visuals; }
	bool getActive() { return m_active; }
	void setState(GameState state) { m_state = state; }
	void setActive(bool active) { m_active = active; }
	void setCollided(bool collide) { m_collided = collide; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	void setScore(int score) { m_score = score; }
	void setBehaviourState(BehaviourState *state) { m_currentBehaviour = state; }

	void generatePath(double dt);
	void handleTimer();
	void setPosition(sf::Vector2f pos);

	double findLargest(std::map<Direction, double> vec);
	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	double getTime() { return m_currentTime; }
	double getTotalRotation() { return m_totalRotations; }
	double getAverageRotations();

	sf::Color getColor() { return m_color; }

	int getScore() { return m_score; }
	int getNodeIndex() { return m_nodeIndex; }
	int getId() { return m_id; }
	int getRadius() { return m_radius; }

	void resetGame();
	void resetDemo();
	void calculateRotations();

	std::string getName() { return "Blended Interpolation"; }
private:

	GameState m_state;
	BehaviourState* m_currentBehaviour;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_prevDirection;
	sf::Vector2f m_curPrevious;
	sf::Vector2f m_heading;
	sf::Vector2f curDirection = sf::Vector2f(0, 0);

	steering m_steering;

	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::RectangleShape m_rect;
	sf::CircleShape m_surroundingCircle;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;
	
	ContextDecisionMaker mapDecisions;

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	float m_speed;
	double m_rotation;
	double MAX_SPEED;
	double curLargest = 0;
	double curLargestDanger = 0;
	

	std::vector<DirectionalLine> m_lineVec;
	std::vector<Obstacle*> m_obstacles;
	std::vector<GameNode*> m_nodes;
	std::vector<Path*> m_pathLine;

	int currentNode = 0;
	int m_radius = 30;
	int currentObs = 0;
	int m_size = 16;
	int m_id = 3;
	int m_score = 0;
	int m_nodeIndex = 0;

	bool m_visuals = true;
	bool m_startTimer = false;
	bool m_active = false;
	bool m_collided = false;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	sf::Color m_color;
	sf::Clock m_clock2;
	sf::Clock m_clock;
	sf::Time m_time;
	
	double m_timeAmount = 0;
	double m_totalPathLength = 0;
	double m_currentTime;
	double m_timeEfficiency;
	double m_averageExecTime;
	double m_tickCounter;
	double m_lastUpdate;
	double m_timer;
	double m_lastRotation;
	double m_totalRotations = 0;


	
	
};
