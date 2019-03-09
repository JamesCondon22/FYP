#include "Headers/Button.h"


Button::Button(sf::Vector2f pos, float width, float height, sf::Texture & texture, sf::Font & font, std::string label) :
	m_position(pos),
	m_width(width),
	m_height(height),
	m_font(font),
	m_label(label)
{
	m_rect.setSize(sf::Vector2f(m_width, m_height));
	m_rect.setPosition(m_position);
	m_rect.setFillColor(sf::Color::White);
	m_rect.setTexture(&texture);

	
	m_text.setString(label);
	m_text.setFont(m_font);
	m_text.setCharacterSize(100);

	auto currentW = m_text.getGlobalBounds().width / 2;
	auto currentH = m_text.getGlobalBounds().height / 2;
	m_text.setOrigin(currentW, currentH);
	m_text.setPosition(m_position.x + (m_width / 2), m_position.y + 60);
	m_text.setFillColor(sf::Color::Black);

}

void Button::setString(std::string label)
{
	m_label = label;
}

Button::~Button()
{

}

void Button::update()
{
	if (m_pressed)
	{
		m_text.setFillColor(sf::Color::White);
	}
}


bool Button::checkCollision(sf::Vector2i & pos)
{
	if (pos.x > m_position.x && pos.x < m_position.x + m_width &&
		pos.y > m_position.y && pos.y < m_position.y + m_height)
	{
		return true;	
	}
	else
	{
		return false;
	}
}

void Button::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	window.draw(m_text);
}