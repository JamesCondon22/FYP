#include "../Include/Headers/ContextMap.h"


/// <summary>
/// initialises the context map 
/// </summary>
/// <param name="noOfDirections">the amount of directions</param>
/// <param name="mapValue">the map value</param>
ContextMap::ContextMap(int noOfDirections, std::map<Direction, double> mapValue)
{
	initVec(noOfDirections, mapValue);
}

void ContextMap::initVec(int noOfDirections, std::map<Direction, double> mapValue)
{
}
/// <summary>
/// returns the size of the map
/// </summary>
/// <returns></returns>
int ContextMap::getSize()
{
	return m_mapVector.size();
}

void ContextMap::multiplyContext(std::map<Direction, double> vec, std::map<Direction, double> vec2)
{
	for (auto it = m_mapVector.begin(); it != m_mapVector.end(); ++it)
	{
		m_mapVector[it->first] = vec[it->first] * vec2[it->first];
	}
}

/// <summary>
/// inserts the values into the map 
/// append the values intot he local map vector 
/// </summary>
/// <param name="vec"></param>
void ContextMap::append(std::map<Direction, double> vec)
{
	m_mapVector.insert(vec.begin(), vec.end());
}

/// <summary>
/// returns the map 
/// </summary>
/// <returns>map </returns>
std::map<Direction, double> ContextMap::returnVec()
{
	return m_mapVector;
}

/// <summary>
/// finds the largest values in the map and
/// returns the state that contains this value
/// </summary>
/// <returns>direction</returns>
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

/// <summary>
/// blends the previous and current context map values 
/// </summary>
/// <param name="vec">the current map</param>
/// <param name="vec2">the previous map</param>
void ContextMap::blendMaps(std::map<Direction, double> vec, std::map<Direction, double> vec2)
{
	for (auto it = m_mapVector.begin(); it != m_mapVector.end(); ++it)
	{
		m_mapVector[it->first] = (vec[it->first] + vec2[it->first]) / 2;
	}

	
}
