#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#pragma comment(lib,"lib/libyaml-cppmdd")
#pragma comment(lib,"lib/thor-d.lib")
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#pragma comment(lib,"lib/libyaml-cppmdd")
#pragma comment(lib,"lib/thor.lib")
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 
#pragma comment(lib,"lib/libyaml-cppmdd")


#include "../Include/Headers/Game.h"

/// <summary>
/// @brief starting point for all C++ programs.
/// 
/// Create a game object and run it.
/// </summary>
/// <param name=""></param>
/// <param name="argv"></param>
/// <returns></returns>
int main(int, char* argv[])
{

	sf::Vector2f currVec = sf::Vector2f(-1, -0.01);
	currVec = Math::normalize(currVec);

	sf::Vector2f desiredVec = sf::Vector2f(50, 50);
	desiredVec = Math::normalize(desiredVec);

	double currAngle = thor::polarAngle(currVec);
	double desiredAngle = thor::polarAngle(desiredVec);
	Game game;
	game.run();
}