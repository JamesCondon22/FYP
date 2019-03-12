#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

class Label
{
public:
	Label(sf::Font & font, sf::Vector2f & pos);
	void setPosition(sf::Vector2f pos) { m_position = pos; }
	void render(sf::RenderWindow & window);
	void setText(std::string text);

private:

	sf::Vector2f m_position;

	sf::Text m_text;
	sf::Font m_font;
};
