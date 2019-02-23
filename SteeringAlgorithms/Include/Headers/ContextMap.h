#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>

#include "MathHelper.h"
//#include 

enum class Direction
{	
	E, ESE, SE, SSE,
	S, SSW, SW, WSW,
	W, WNW, NW, NNW,
	N, NNE, NE, ENE,
};

class ContextMap
{
public:
	ContextMap(int noOfDirections, std::map<Direction, double> mapValue);
	ContextMap() { ; }
	~ContextMap() { ; }
	void initVec(int noOfDirections, std::map<Direction, double> mapValue);
	int getSize();
	std::map<Direction, double> returnVec();
	void append(std::map<Direction, double> vec);
	void multiplyContext(std::map<Direction, double> vec, std::map<Direction, double> vec2);
	Direction findLargest();
	double findInterpolatingValue();

	std::map<Direction, double> mapInterpolation(std::map<Direction, double> vec, std::map<Direction, double> vec2);
	
private:
	std::map<Direction, double> m_mapVector;

};

