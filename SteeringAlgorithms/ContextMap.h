#pragma once
#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
//#include 


class ContextMap
{
public:
	ContextMap(int noOfDirections, std::pair<double, std::string > mapValue);
	ContextMap();
	~ContextMap();
	void initVec(int noOfDirections, std::pair<double, std::string > mapValue);
	int getSize();
	std::vector<std::pair<double, std::string>> returnVec();
	void append(std::vector<std::pair<double, std::string>> vec);
	void appendAndMult(std::vector<std::pair<double, std::string>> vec, std::vector<std::pair<double, std::string>> vec2);
	std::pair<double, std::string> findLargest();

private:
	std::vector<std::pair<double, std::string>> m_mapVector;
};

