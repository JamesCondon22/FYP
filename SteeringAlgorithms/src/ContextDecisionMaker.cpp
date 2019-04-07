#include "../Include/Headers/ContextDecisionMaker.h"

/// <summary>
/// initialises the default maps 
/// </summary>
ContextDecisionMaker::ContextDecisionMaker() { 
	m_PrevContext = ContextMap();
	newMap = ContextMap();
}


ContextDecisionMaker::~ContextDecisionMaker()
{

}

/// <summary>
/// fills the values intot he danger map
/// appends the distances into map format
/// </summary>
/// <param name="map">the current context map</param>
/// <param name="distances">the distance values</param>
/// <returns></returns>
ContextMap ContextDecisionMaker::FillDangerMap(ContextMap map, std::map<Direction, double> distances)
{
	map.append(distances);
	return map;
}

/// <summary>
/// fills the interest context map 
/// multiplies the dangers against the interest 
/// </summary>
/// <param name="danger">the danger map</param>
/// <param name="interest">the interest map</param>
/// <param name="distances">the interest distances</param>
/// <returns></returns>
ContextMap ContextDecisionMaker::FillInterestMap(ContextMap danger, ContextMap interest, std::map<Direction, double> distances)
{
	interest.append(distances);
	interest.multiplyContext(distances, danger.returnVec());

	return interest;
}

/// <summary>
/// blends the previous and current context maps 
/// </summary>
/// <param name="previous">previous context map</param>
/// <param name="current">current context map</param>
/// <returns></returns>
ContextMap ContextDecisionMaker::FillBlendMap(ContextMap previous, ContextMap current)
{
	previous.blendMaps(previous.returnVec(), current.returnVec());
	
	return previous;
}

/// <summary>
/// updates the context maps 
/// sets the strongest interest in the map 
/// this will be the direction in which the ai will travel
/// </summary>
/// <param name="distances">the interests </param>
/// <param name="dangerDist">the dangers</param>
void ContextDecisionMaker::update(std::map<Direction, double> distances, std::map<Direction, double> dangerDist)
{
	ContextMap dangerMap = ContextMap();
	ContextMap interestMap = ContextMap();

	dangerMap = FillDangerMap(dangerMap, dangerDist);
	interestMap = FillInterestMap(dangerMap, interestMap, distances);
	
	strongestInterest = interestMap.findLargest();

	newMap = FillBlendMap(m_PrevContext, interestMap);
	//bleded value of the maps 
	blendedInterest = newMap.findLargest();
	//sets the previous context map
	m_PrevContext = interestMap;

	if (previous != strongestInterest)
	{
		realPrevious = previous;
	}

	previous = strongestInterest;
}

/// <summary>
/// returns the strongest direction
/// </summary>
/// <returns></returns>
Direction ContextDecisionMaker::getStrongest()
{
	return strongestInterest;
}

/// <summary>
/// returns the blended direction 
/// </summary>
/// <returns></returns>
Direction ContextDecisionMaker::getBlendedStrongest()
{
	return blendedInterest;
}

/// <summary>
/// returns the previous direction
/// </summary>
/// <returns></returns>
Direction ContextDecisionMaker::getPrevious()
{
	return realPrevious;
}

/// <summary>
/// returns a vector 
/// this is an average of all strongest interest 
/// and two directions either side of the strongest 
/// </summary>
/// <returns></returns>
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
