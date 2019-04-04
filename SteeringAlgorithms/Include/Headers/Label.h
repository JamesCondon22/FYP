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
	void setOutline(sf::Color color, float thicknes);
	sf::Color getColor();
	sf::Vector2f getPosition() { return m_position; }
	void update();
private:

	sf::Vector2f m_position;

	sf::Text m_text;
	sf::Font m_font;

	float m_alpha = 255.0f;
	bool m_animateIn = true;
	bool m_animateOut = false;
};
