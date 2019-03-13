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
#include "../spline_library/splines/uniform_cr_spline.h"

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
	/*std::vector<sf::Vector2f> splinePoints{
		sf::Vector2f(0, 0),
		sf::Vector2f(5, 0),
		sf::Vector2f(8, 3),
		sf::Vector2f(6, 1),
	};
	UniformCRSpline<sf::Vector2f> mySpline(splinePoints);
	sf::Vector2f interpolatedPosition = mySpline.getPosition(0.5f);
	*/

	Game game;
	game.run();
}