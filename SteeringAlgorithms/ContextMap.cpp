#include "ContextMap.h"



ContextMap::ContextMap(int noOfDirections, std::map<Direction, double> mapValue)
{
	initVec(noOfDirections, mapValue);
}

void ContextMap::initVec(int noOfDirections, std::map<Direction, double> mapValue)
{
}

int ContextMap::getSize()
{
	return m_mapVector.size();
}

void ContextMap::appendAndMult(std::map<Direction, double> vec, std::map<Direction, double> vec2)
{
	for (auto it = m_mapVector.begin(); it != m_mapVector.end(); ++it)
	{
		m_mapVector[it->first] = vec[it->first] * vec2[it->first];
	}
}

void ContextMap::append(std::map<Direction, double> vec)
{
	m_mapVector.insert(vec.begin(), vec.end());
}

std::map<Direction, double> ContextMap::returnVec()
{
	return m_mapVector;
}

Direction ContextMap::findLargest()
{
	double largest = 0;
	Direction curDir = Direction::N;
	std::map<Direction, double> map;
	for (auto it = m_mapVector.begin(); it != m_mapVector.end(); ++it)
	{
		if (it->second > largest) {
			map.clear();
			largest = it->second;
			curDir = it->first;
			map.insert({ curDir, largest });
		}

	}
	return curDir;
}

double ContextMap::findInterpolatingValue()
{
	return 0.0;
}
