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
ContextMap ContextDecisionMaker::FillInterestMap(ContextMap danger, ContextMap interest, std::vector<double> distances)
{
	interest.appendVector(distances);
	return interest;
}

void ContextDecisionMaker::update(std::vector<double> distances)
{
	ContextMap dangerMap = ContextMap(noOfDirections, 0.0f);
	ContextMap interestMap = ContextMap(noOfDirections, 0.0f);

	interestMap = FillInterestMap(dangerMap, interestMap, distances);
	
	strongestInterest = interestMap.findLargest();
}

double ContextDecisionMaker::getStrongest()
{
	return strongestInterest;
}
