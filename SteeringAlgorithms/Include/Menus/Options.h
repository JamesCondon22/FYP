#pragma once
#ifndef OPTIONS
#define OPTIONS
#include <SFML\Graphics.hpp>
#include "Menus/State.h"
#include <fstream>
#include "Headers/Label.h"
#include "Headers/Button.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui-SFML.h"

class Options
{
public:
	Options(GameState * state, sf::Font & font, sf::Font & btnfont, sf::Texture & texture, sf::RenderWindow & window);
	~Options();
	void update(double dt);
	void render(sf::RenderWindow& window);
	void loadData();
	bool m_pressed = false;
private:

	GameState * m_currentState;
	sf::RenderWindow * m_window;
	sf::Vector2f m_position;

	std::string m_line;
	std::ifstream m_file;
	bool m_written = false;
	bool m_full = false;

	sf::Texture m_texture;
	sf::Text m_text;
	sf::Font m_font;
	std::vector<Label*> m_labels;

	float sliderVal;
	char buf[32];
	sf::Clock m_clock;
	Button * button;
	
	ImFont * m_guiText;
	bool m_loaded = false;
	sf::Vector2i m_mousePositon;
};
#endif // !Options
