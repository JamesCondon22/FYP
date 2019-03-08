#ifndef MAINMENU
#define MAINMENU	
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"

class MainMenu
{
public:
	MainMenu(GameState * state);
	~MainMenu();
	void update(double dt);
	void render(sf::RenderWindow& window);

private:

	GameState * m_currentState;
	sf::Window m_window;
};
#endif // !