#pragma once

#include <SFML/Graphics.hpp>
#include "ContextMap.h"
#include <string.h>

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
	ContextMap FillDangerMap(ContextMap map, std::vector<std::pair<double, std::string>> distances);
	ContextMap FillInterestMap(ContextMap danger, ContextMap interest, std::vector<std::pair<double, std::string>> distances);
	std::pair<double, std::string> getStrongest();
	void update(std::vector<std::pair<double, std::string>> distances, std::vector<std::pair<double, std::string>> dangers);
private:
	int noOfDirections = 8;
	std::pair<double, std::string> strongestInterest;
};

