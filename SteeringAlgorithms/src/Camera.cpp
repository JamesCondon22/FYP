#include "Headers/Camera.h"

Camera::Camera(sf::Vector2f & size)
{
	m_view.setSize(size);
}


void Camera::update()
{
	m_view.setCenter(m_position);
}


void Camera::setRect(sf::FloatRect rect)
{
	m_view.setViewport(sf::FloatRect(rect));
}


void Camera::setPosition(sf::Vector2f pos)
{
	m_position = pos;
}


void Camera::setZoom(float zoom)
{
	m_view.zoom(zoom);
}


void Camera::render(sf::RenderWindow & window)
{
	window.setView(m_view);
}
