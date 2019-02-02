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
	/*m_mapVector[0].first = vec[0].first * vec2[0].first; m_mapVector[4].first = vec[4].first * vec2[4].first;
	m_mapVector[1].first = vec[1].first * vec2[1].first; m_mapVector[5].first = vec[5].first * vec2[5].first;
	m_mapVector[2].first = vec[2].first * vec2[2].first; m_mapVector[6].first = vec[6].first * vec2[6].first;
	m_mapVector[3].first = vec[3].first * vec2[3].first; m_mapVector[7].first = vec[7].first * vec2[7].first;*/
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
