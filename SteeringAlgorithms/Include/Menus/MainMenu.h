#ifndef MAINMENU
#define MAINMENU	
#include <SFML\Graphics.hpp>
#include "SFML\Audio.hpp"
#include "State.h"
#include "Headers/Button.h"

class MainMenu
{
public:
	MainMenu(GameState * state);
	~MainMenu();
	void update(double dt);
	void render(sf::RenderWindow& window);
	void initButtons();

private:

	GameState * m_currentState;
	sf::Window m_window;

	std::vector<Button*> m_buttons;
	sf::Texture m_texture;

	sf::Font m_font;
};
#endif // !