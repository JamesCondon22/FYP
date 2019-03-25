#pragma once
#include <SFML/Graphics.hpp>

class Camera
{
public:
	Camera() { ; }
	Camera(sf::Vector2f & size);
	~Camera() { ; }
	void update();
	void render(sf::RenderWindow & window);
	void setPosition(sf::Vector2f pos);
	void setRect(sf::FloatRect rect);
	sf::Vector2f getPosition() { return m_position; }
	void setZoom(float zoom);
private:
	sf::Vector2f m_position;
	sf::View m_view;
	
};
