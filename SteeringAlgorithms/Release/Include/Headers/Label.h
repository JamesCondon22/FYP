#pragma once

#include <SFML\Graphics.hpp>
#include <iostream>

class Label
{
public:
	Label(sf::Font & font, sf::Vector2f  pos);
	void setPosition(sf::Vector2f pos);
	void render(sf::RenderWindow & window);
	void setText(std::string text);
	void setSize(int size);
	void setColor(sf::Color color);
	sf::Color getColor();
	sf::Vector2f getPosition() { return m_position; }
private:

	sf::Vector2f m_position;

	sf::Text m_text;
	sf::Font m_font;
};
