#include "Headers/Lifebar.h"

LifeBar::LifeBar(sf::Vector2f position) :
	m_position(position),
	m_life(580.0f)
{
	m_bordeRect.setPosition(m_position);
	m_bordeRect.setFillColor(sf::Color(0, 0, 0, 157));
	m_bordeRect.setSize(sf::Vector2f(600.0f, 75.0f));

	m_lifeRect.setPosition(m_position.x + 10,  m_position.y + 10);
	m_lifeRect.setFillColor(sf::Color::Green);
	m_lifeRect.setSize(sf::Vector2f(m_life, 55.0f));
	
}

LifeBar::~LifeBar() {

}

void LifeBar::update() {

	if (m_life > 0 && m_life <= 100) {
		m_alpha -= 5;
		m_lifeRect.setFillColor(sf::Color(255,0,0, m_alpha));
	}
	
}


void LifeBar::deplete() {
	if (m_life > 0) {
		m_life -= 1.0f;
		m_lifeRect.setSize(sf::Vector2f(m_life, 55.0f));
	}

	if (m_life > 100 && m_life <= 193) {
		m_lifeRect.setFillColor(sf::Color::Red);
	}
	if (m_life > 193 && m_life <= 386) {
		m_lifeRect.setFillColor(sf::Color(255, 140, 0));
	}
}


void LifeBar::reset() {

	m_life = 580.0f;
	m_lifeRect.setFillColor(sf::Color::Green);
	m_lifeRect.setSize(sf::Vector2f(m_life, 55.0f));
}


void LifeBar::render(sf::RenderWindow & window) {

	window.draw(m_bordeRect);
	window.draw(m_lifeRect);
}