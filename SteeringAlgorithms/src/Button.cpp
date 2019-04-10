#include "Headers/Button.h"

/// <summary>
/// initialises all the button data 
/// sets the position, width, height font and string
/// </summary>
/// <param name="pos">position of the button</param>
/// <param name="width">width of the button</param>
/// <param name="height">height of the button</param>
/// <param name="texture">the button texture</param>
/// <param name="font">the button font</param>
/// <param name="label">the label of the button</param>
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
	//sets the text depending on the width and height of the button 
	m_text.setOrigin(currentW, currentH);
	m_text.setPosition(m_position.x + (m_width / 2), m_position.y + 40);
	m_text.setFillColor(sf::Color::White);

}
/// <summary>
/// sets the string on the button
/// </summary>
/// <param name="label">the string on the button</param>
void Button::setString(std::string label)
{
	m_label = label;
}

Button::~Button()
{

}

/// <summary>
/// updates to button to check if its 
/// pressed 
/// </summary>
void Button::update()
{
	if (m_pressed)
	{
		m_text.setFillColor(sf::Color::Black);
	}
	else {
		m_text.setFillColor(sf::Color::White);
	}
}

/// <summary>
/// checks for colision between the between the mouse 
/// and the button 
/// </summary>
/// <param name="pos">the mouse position</param>
/// <returns></returns>
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

/// <summary>
/// renders the button
/// </summary>
/// <param name="window"></param>
void Button::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
	window.draw(m_text);
}