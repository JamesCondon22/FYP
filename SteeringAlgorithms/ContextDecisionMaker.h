#pragma once

#include <SFML/Graphics.hpp>
#include "ContextMap.h"

enum Direction {

	UP,
	UPRIGHT,
	RIGHT,
	DOWNRIGHT,
	DOWN,
	DOWNLEFT,
	LEFT,
	UPLEFT,
	NONE
};

class ContextDecisionMaker
{
public:
	ContextDecisionMaker();
	~ContextDecisionMaker();
	void FillDangerMap(ContextMap map, sf::Vector2f position);
	ContextMap FillInterestMap(ContextMap danger, ContextMap interest, std::vector<double> distances);
	double getStrongest();
	void update(std::vector<double> distances);
private:
	int noOfDirections = 8;
	double strongestInterest = 0;
};

