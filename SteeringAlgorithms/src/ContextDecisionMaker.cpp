#include "../Include/Headers/ContextDecisionMaker.h"

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

std::vector<int> ContextDecisionMaker::getAverage()
{
	std::vector<int> vec;
	auto current = static_cast<int>(strongestInterest);
	auto next = current + 1;
	auto last = current - 1;
	if (current == 15)
	{
		next = 0;
	}
	auto nextPlus = next + 1;

	if (next == 15)
	{
		nextPlus = 0;
	}

	if (current == 0)
	{
		last = 15;
	}
	auto lastMinus = last - 1;
	if (last == 0)
	{
		lastMinus = 15;
	}
	
	vec.push_back(current);
	vec.push_back(next);
	vec.push_back(nextPlus);
	vec.push_back(last);
	vec.push_back(lastMinus);

	return vec;
}
