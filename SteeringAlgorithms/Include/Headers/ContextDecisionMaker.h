#pragma once

#include <SFML/Graphics.hpp>
#include "ContextMap.h"
#include <string.h>
#include <map>


 //Direction::N

//enum class Direction {
//
//	UP,
//	UPRIGHT,
//	RIGHT,
//	DOWNRIGHT,
//	DOWN,
//	DOWNLEFT,
//	LEFT,
//	UPLEFT,
//	NONE
//};

class ContextDecisionMaker
{
public:
	ContextDecisionMaker() { ; }
	~ContextDecisionMaker();
	ContextMap FillDangerMap(ContextMap map, std::map<Direction, double> distances);
	ContextMap FillInterestMap(ContextMap danger, ContextMap interest, std::map<Direction, double> distances);
	Direction getStrongest();
	std::vector<int> getAverage();
	void update(std::map<Direction, double> distances, std::map<Direction, double> dangers);
private:
	int noOfDirections = 8;
	Direction strongestInterest;
	//std::map<Direction, double> m_strongestInterest;
};

