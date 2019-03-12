#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include <fstream>
#include "Headers/Label.h"

class Options
{
public:
	Options(GameState * state, sf::Font & font);
	~Options();
	void update(double dt);
	void render(sf::RenderWindow& window);

private:

	GameState * m_currentState;
	sf::Window m_window;
	sf::Vector2f m_position;

	std::string m_line;
	std::ifstream m_file;
	bool m_written = false;
	bool m_full = false;

	sf::Text m_text;
	sf::Font m_font;
	std::vector<Label*> m_labels;
};
#endif // !Options
