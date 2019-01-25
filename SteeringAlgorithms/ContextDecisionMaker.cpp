#include "ContextDecisionMaker.h"



ContextDecisionMaker::ContextDecisionMaker()
{
	
}


ContextDecisionMaker::~ContextDecisionMaker()
{
}

ContextMap ContextDecisionMaker::FillDangerMap(ContextMap map, std::vector<std::pair<double, std::string>> distances)
{
	map.append(distances);
	return map;
}
ContextMap ContextDecisionMaker::FillInterestMap(ContextMap danger, ContextMap interest, std::vector<std::pair<double, std::string>> distances)
{
	interest.append(distances);
	interest.appendAndMult(distances, danger.returnVec());

	return interest;
}

void ContextDecisionMaker::update(std::vector<std::pair<double, std::string>> distances, std::vector<std::pair<double, std::string>> dangerDist)
{
	ContextMap dangerMap = ContextMap(noOfDirections, std::make_pair(0.0f, "NONE"));
	ContextMap interestMap = ContextMap(noOfDirections, std::make_pair(0.0f, "NONE"));

	dangerMap = FillDangerMap(dangerMap, dangerDist);
	interestMap = FillInterestMap(dangerMap, interestMap, distances);
	
	strongestInterest = interestMap.findLargest();
	std::cout << interestMap.findLargest().first << std::endl;
}

std::pair<double, std::string> ContextDecisionMaker::getStrongest()
{
	return strongestInterest;
}
