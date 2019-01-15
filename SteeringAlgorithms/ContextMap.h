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
	std::vector<double> returnVec();
	void appendVector(std::vector<double> vec);
	double findLargest();
private:
	std::vector<double> m_mapVector;
};

