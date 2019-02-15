#include "ContextDecisionMaker.h"

ContextDecisionMaker::~ContextDecisionMaker()
{
}

ContextMap ContextDecisionMaker::FillDangerMap(ContextMap map, std::map<Direction, double> distances)
{
	map.append(distances);
	return map;
}
ContextMap ContextDecisionMaker::FillInterestMap(ContextMap danger, ContextMap interest, std::map<Direction, double> distances)
{
	interest.append(distances);
	interest.appendAndMult(distances, danger.returnVec());

	return interest;
}

void ContextDecisionMaker::update(std::map<Direction, double> distances, std::map<Direction, double> dangerDist)
{
	ContextMap dangerMap = ContextMap();
	ContextMap interestMap = ContextMap();

	dangerMap = FillDangerMap(dangerMap, dangerDist);
	interestMap = FillInterestMap(dangerMap, interestMap, distances);
	
	strongestInterest = interestMap.findLargest();
}

Direction ContextDecisionMaker::getStrongest()
{
	return strongestInterest;
}
