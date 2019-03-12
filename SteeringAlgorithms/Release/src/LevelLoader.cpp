#include "../Include/Headers/LevelLoader.h"
#include <time.h>
void operator >> (const YAML::Node& obstacleNode, ObstacleData& obstacle)
{
	obstacle.m_type = obstacleNode["type"].as<std::string>();
	obstacle.m_position.x = obstacleNode["position"]["x"].as<float>();
	obstacle.m_position.y = obstacleNode["position"]["y"].as<float>();
	obstacle.m_radius = obstacleNode["radius"].as<int>();
	obstacle.m_id = obstacleNode["id"].as<int>();
}
void operator >> (const YAML::Node& pathNode, PathData& path)
{
	path.m_type = pathNode["type"].as<std::string>();
	path.m_position.x = pathNode["position"]["x"].as<float>();
	path.m_position.y = pathNode["position"]["y"].as<float>();

}

void operator >> (const YAML::Node& levelNode, LevelData& level)
{
	

	const YAML::Node& obstaclesNode = levelNode["circles"].as<YAML::Node>();
	for (unsigned i = 0; i < obstaclesNode.size(); ++i)
	{

		ObstacleData obstacle;
		obstaclesNode[i] >> obstacle;
		level.m_obstacles.push_back(obstacle);
	}

	const YAML::Node& pathNode = levelNode["paths"].as<YAML::Node>();
	for (unsigned i = 0; i < pathNode.size(); ++i)
	{

		PathData path;
		pathNode[i] >> path;
		level.m_paths.push_back(path);
		level.send(path);
		level.current = path.m_position;
	}

	
}
LevelLoader::LevelLoader()
{
}

bool LevelLoader::load(int nr, LevelData& level)
{
	std::stringstream ss;
	ss << "./resources/levels/level";
	ss << nr;
	ss << ".yaml";

	try
	{
		YAML::Node baseNode = YAML::LoadFile(ss.str());
		if (baseNode.IsNull())
		{
			std::string message("file: " + ss.str() + " not found");
			throw std::exception(message.c_str());
		}
		baseNode >> level;
	}
	catch (YAML::ParserException& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}
	catch (std::exception& e)
	{
		std::cout << e.what() << "\n";
		return false;
	}

	return true;
}

PathData LevelData::send(PathData data)
{
	return data;
}