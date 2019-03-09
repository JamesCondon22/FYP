#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>

class Button
{
public:
	Button() { ; }
	Button(sf::Vector2f size, float width, float height, sf::Texture & texture, sf::Font & font, std::string string);
	~Button();

	bool checkCollision(sf::Vector2i & pos);
	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();
	void setString(std::string label);
	void update();
	void render(sf::RenderWindow & window);

	std::string getString() { return m_label; }

	void setPressed(bool pressed) { m_pressed = pressed; }
private:
	
	sf::Vector2f m_position;
	sf::RectangleShape m_rect;
	

	float m_speed;
	std::string m_label;

	float m_width;
	float m_height;

	sf::Text m_text;
	sf::Font m_font;

	bool m_pressed;
};