#include "ContextDecisionMaker.h"



ContextDecisionMaker::ContextDecisionMaker()
{
	
}


ContextDecisionMaker::~ContextDecisionMaker()
{
}

void ContextDecisionMaker::FillDangerMap(ContextMap map, sf::Vector2f position)
{

}
void ContextDecisionMaker::FillInterestMap(ContextMap danger, ContextMap interest, sf::Vector2f position)
{
	for (int i = 0; i < interestMap.getSize(); i++)
	{
		//if (position.x )
	}
}

void ContextDecisionMaker::update(sf::Vector2f position)
{
	dangerMap = ContextMap(noOfDirections, 0.0f);
	interestMap = ContextMap(noOfDirections, 0.0f);

	FillInterestMap(dangerMap, interestMap, position);

}
