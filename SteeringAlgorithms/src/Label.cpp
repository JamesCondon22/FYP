#include "Headers/Label.h"


Label::Label(sf::Font & font, sf::Vector2f & pos) :
	m_font(font),
	m_position(pos)
{
	m_text.setFont(m_font);
	m_text.setCharacterSize(30);
	m_text.setFillColor(sf::Color::Black);
	m_text.setPosition(m_position);
}

void Label::setText(std::string text)
{
	m_text.setString(text);
}


void Label::render(sf::RenderWindow & window)
{
	window.draw(m_text);
}

