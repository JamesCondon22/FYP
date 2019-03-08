#include "Headers/Button.h"


Button::Button(sf::Vector2f pos, float width, float height, sf::Texture & texture) :
	m_position(pos),
	m_width(width),
	m_height(height)
{
	m_rect.setSize(sf::Vector2f(m_width, m_height));
	m_rect.setPosition(m_position);
	m_rect.setFillColor(sf::Color::White);
	m_rect.setTexture(&texture);
}

Button::~Button()
{

}

void Button::update()
{

}

void Button::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}