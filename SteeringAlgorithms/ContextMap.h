#pragma once
#include <iostream>
#include <vector>


class ContextMap
{
public:
	ContextMap(int noOfDirections, float mapValue);
	ContextMap();
	~ContextMap();
	void initVec(int noOfDirections, float mapValue);
	int getSize();


private:
	std::vector<std::pair<float, float>> m_mapVector;
};

