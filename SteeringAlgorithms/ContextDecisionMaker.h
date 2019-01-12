#pragma once

#include <SFML/Graphics.hpp>
#include "ContextMap.h"

enum Direction {

	UP,
	DOWN,
	LEFT,
	RIGHT,
	NONE
};

class ContextDecisionMaker
{
public:
	ContextDecisionMaker();
	~ContextDecisionMaker();
	void FillDangerMap(ContextMap map, sf::Vector2f position);
	void FillInterestMap(ContextMap danger, ContextMap interest, sf::Vector2f position);

	void update(sf::Vector2f position);
private:
	int noOfDirections = 8;

	ContextMap dangerMap;
	ContextMap interestMap;
};

