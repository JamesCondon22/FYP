#pragma once
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include <fstream>
#include "Headers/Label.h"

class EndGame
{
public:
	EndGame(GameState * state, sf::Font & font);
	~EndGame();
	void update(double dt);
	void render(sf::RenderWindow& window);

private:

	GameState * m_currentState;
	sf::RenderWindow * m_window;
	sf::Vector2f m_position;

	std::string m_line;
	std::ifstream m_file;

	sf::Text m_text;
	sf::Font m_font;
	std::vector<Label*> m_labels;
	sf::Clock m_clock;
	bool m_loaded = false;
};
