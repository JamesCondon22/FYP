#pragma once
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include <fstream>
#include "Headers/UI/Label.h"
#include "Headers/UI/Button.h"

class EndGame
{
public:
	EndGame(GameState * state, sf::Font & font);
	~EndGame() { ; }
	void update(double dt, sf::Window & window);
	void render(sf::RenderWindow& window);
	bool m_pressed = false;
private:

	GameState * m_currentState;
	sf::RenderWindow * m_window;
	sf::Vector2f m_position;
	sf::Vector2i m_mousePosition;
	std::string m_line;
	std::ifstream m_file;
	sf::Texture m_texture;
	sf::Text m_text;
	sf::Font m_font;
	std::vector<Label*> m_labels;
	sf::Clock m_clock;

	Button * m_backButton;
	bool m_loaded = false;
	
};
