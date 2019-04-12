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
#include "../spline/spline/src/main/cpp/CatmullRom.h"

class CRSplineAI : public Enemy
{
public:
	CRSplineAI(std::vector<GameNode*> path, std::vector<Obstacle*>  obs);
	CRSplineAI() { ; }
	~CRSplineAI();

	void update(double dt, sf::Vector2f position);
	void updatePlotPoints(double dt, sf::Vector2f position);
	void render(sf::RenderWindow & window);

	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getCurrentNodePosition();
	sf::Vector2f normalize(sf::Vector2f vec);

	steering seek(sf::Vector2f position);

	void updateLines(sf::Vector2f position);
	void updateDangers();
	void initVector();
	void checkDirection();
	void calculation();

	std::map<Direction, double> normalize(std::map<Direction, double> vec);
	std::map<Direction, double> normalizeDangers(std::map<Direction, double> vec);
	
	double findLargest(std::map<Direction, double> vec);

	float getNewOrientation(float curOrientation, sf::Vector2f velocity);
	float length(sf::Vector2f vel);

	int getId() { return m_id; }
	int getScore() { return m_score; }
	int getRadius() { return m_radius; }
	int getNodeIndex() { return m_nodeIndex; }
	int getClosestNode() { return m_closestNode; }
	int m_counter = 0;

	bool getCollided() { return m_collided; }
	bool pathset = false;
	bool getVisuals() { return m_visuals; }
	bool getActive() { return m_active; }
	void setActive(bool active) { m_active = active; }
	void setCollided(bool collide) { m_collided = collide; }
	void setScore(int score) { m_score = score; }
	void setVisuals(bool visuals) { m_visuals = visuals; }
	void setBehaviourState(BehaviourState *state) { m_currentBehaviour = state; }
	void setState(GameState state) { m_state = state; }

	double getTime() { return m_currentTime; }
	double getPathLength() { return m_totalPathLength; }
	double getInterceptionTime() { return m_currentTime; }
	double getAverageExecTime();
	double getTotalRotation() { return m_totalRotations; }
	double getAverageRotations();

	void setTag(std::string tag) { m_tag = tag; }
	void calculateRotations();
	void findClosestNode();
	void setColor(sf::Color color) { m_color = color; }
	void setSpeed(float speed) { m_speed = speed; }
	void setCurve(Curve * curve) { m_curve = curve; }
	void setPosition(sf::Vector2f pos);
	void setRadius(int rad) { m_radius = rad; }
	void generatePath(double dt);
	void handleTimer();

	sf::Color getColor() { return m_color; }
	sf::Vector2f getPointPosition();

	double checkDistance(sf::Vector2f position);
	double getTicks() { return m_tickCounter; }
	
	void resetDemo();
	void resetCurve();
	void resetGame();
	
	Curve * getCurve() { return m_curve; }

	std::string getTag() { return m_tag; }
	std::string getName() { return "Catmull Rom AI"; }

private:

	BehaviourState * m_currentBehaviour;
	GameState m_state;
	Curve * m_curve;

	ContextDecisionMaker mapDecisions;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;

	steering m_steering;

	sf::RectangleShape m_rect;
	sf::Sprite m_sprite;
	sf::Texture m_texture;

	double static const DEG_TO_RAD;
	double static const RAD_TO_DEG;

	sf::Vector2f m_heading;
	
	sf::CircleShape m_surroundingCircle;

	std::map<Direction, double> m_distances;
	std::map<Direction, double> m_distancesDanger;

	double m_rotation;
	double MAX_SPEED;
	double curLargest = 0;
	double curLargestDanger = 0;
	float m_speed;

	sf::Vector2f curDirection = sf::Vector2f(0, 0);
	sf::Vector2f m_futurePos = sf::Vector2f(0, 0);

	std::vector<GameNode*> m_nodes;
	std::vector<Obstacle*> m_obstacles;
	std::vector<DirectionalLine> m_lineVec;
	std::vector<Path*> m_pathLine;
	std::vector<sf::CircleShape> m_romPoints;

	int m_currentNode = 0;
	int m_currentObs = 0;
	int m_size = 16;
	int m_id = 6;
	int m_radius = 30;

	bool m_active = false;
	bool m_collided = false;
	bool m_startTimer = false;

	double m_lastRotation;
	double m_totalRotations = 0;
	double m_currentTime;
	double m_timeAmount = 0;
	double m_totalPathLength = 0;

	Path * m_currentPathCircle;
	Path * m_lastPathCircle;

	sf::Color m_color;
	sf::Clock m_clock;
	sf::Time m_time;

	double m_timeEfficiency;
	double m_averageExecTime;
	double m_tickCounter;
	double m_lastUpdate;
	double m_timer;

	sf::Vector2f m_currentTargetPos = sf::Vector2f(0, 0);
	
	bool m_visuals = true;
	bool m_inRange = false;

	int m_score = 0;
	int m_savedNode = 0;
	int m_nodeIndex = 0;
	int m_closestNode = 0;
	
	std::string m_tag;
};
