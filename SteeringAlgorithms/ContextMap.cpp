#include "ContextMap.h"



ContextMap::ContextMap(int noOfDirections, std::pair<double, std::string > mapValue)
{
	initVec(noOfDirections, mapValue);
}

ContextMap::ContextMap()
{

}

ContextMap::~ContextMap()
{

}

void ContextMap::initVec(int noOfDirections, std::pair<double, std::string > mapValue)
{
	m_mapVector.assign(noOfDirections, mapValue);
}

int ContextMap::getSize()
{
	return m_mapVector.size();
}

void ContextMap::appendAndMult(std::vector<std::pair<double, std::string>> vec, std::vector<std::pair<double, std::string>> vec2)
{
	m_mapVector[0].first = vec[0].first * vec2[0].first; m_mapVector[4].first = vec[4].first * vec2[4].first;
	m_mapVector[1].first = vec[1].first * vec2[1].first; m_mapVector[5].first = vec[5].first * vec2[5].first;
	m_mapVector[2].first = vec[2].first * vec2[2].first; m_mapVector[6].first = vec[6].first * vec2[6].first;
	m_mapVector[3].first = vec[3].first * vec2[3].first; m_mapVector[7].first = vec[7].first * vec2[7].first;
	//std::cout << (vec2[0].second) << std::endl;
	
}

void ContextMap::append(std::vector<std::pair<double, std::string>> vec)
{
	m_mapVector[0] = vec[0]; m_mapVector[4] = vec[4];
	m_mapVector[1] = vec[1]; m_mapVector[5] = vec[5];
	m_mapVector[2] = vec[2]; m_mapVector[6] = vec[6];
	m_mapVector[3] = vec[3]; m_mapVector[7] = vec[7];

}

std::vector<std::pair<double, std::string>> ContextMap::returnVec()
{
	return m_mapVector;
}

std::pair<double, std::string> ContextMap::findLargest()
{
	std::sort(m_mapVector.begin(), m_mapVector.end());
	return m_mapVector.at(m_mapVector.size() - 1);

}
