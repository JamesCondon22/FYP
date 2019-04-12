#include "Headers/UI/Key.h"

Key::Key(sf::Texture & texture) :
	m_texture(texture)
{
	m_rect.setTexture(&m_texture);
	m_rect.setPosition(0.0f, 0.0f);
	m_rect.setOrigin(50.0f, 50.0f);
	m_rect.setSize(sf::Vector2f(100.0f, 50.0f));

	m_surround.setRadius(50.0f);
	m_surround.setPosition(0.0f, 0.0f);
	m_surround.setOrigin(50.0f, 25.0f);
}

void Key::update(double dt) {
	m_rect.setPosition(m_position);
	m_surround.setPosition(m_position);
}

void Key::checkCollision(sf::Vector2f position, float rad) {
	if (Math::circleCollision(m_position, position, m_surround.getRadius(), rad)) {
		m_collision = true;
	}
}


void Key::render(sf::RenderWindow & window) {

	window.draw(m_rect);
}