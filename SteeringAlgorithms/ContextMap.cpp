#include "ContextMap.h"



ContextMap::ContextMap(int noOfDirections, float mapValue)
{
	initVec(noOfDirections, mapValue);
}

ContextMap::ContextMap()
{

}

ContextMap::~ContextMap()
{

}

void ContextMap::initVec(int noOfDirections, float value)
{
	m_mapVector.assign(noOfDirections, value);
}

int ContextMap::getSize()
{
	return m_mapVector.size();
}

void ContextMap::appendVector(std::vector<double> vec)
{
	m_mapVector[0] = vec[0]; m_mapVector[4] = vec[4];
	m_mapVector[1] = vec[1]; m_mapVector[5] = vec[5];
	m_mapVector[2] = vec[2]; m_mapVector[6] = vec[6];
	m_mapVector[3] = vec[3]; m_mapVector[7] = vec[7];

	
}

std::vector<double> ContextMap::returnVec()
{
	return m_mapVector;
}

double ContextMap::findLargest()
{
	double largest = 0;
	for (auto iter = m_mapVector.begin(); iter != m_mapVector.end(); ++iter)
	{
		if (*iter > largest)
		{
			largest = *iter;
		}
	}
	return largest;
}
