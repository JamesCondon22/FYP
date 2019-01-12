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
	m_mapVector.assign(noOfDirections, std::make_pair(value, value));
}

int ContextMap::getSize()
{
	return m_mapVector.size();
}
