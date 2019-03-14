#include "../Include/Headers/Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player() :
	m_position(0, 0),
	m_velocity(0, 0),
	size(100),
	m_rotation(0),
	m_speed(0),
	MAX_SPEED(350)
{
	if (!m_texture.loadFromFile("resources/assets/enemy.png")) {
		//do something
	}
	m_rect.setOrigin(m_position.x + 50 / 2, m_position.y + 25 / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(50, 25));
	m_position = sf::Vector2f(900, 500);
	m_rect.setPosition(m_position);

	m_rect.setFillColor(sf::Color::Red);

}


Player::~Player()
{
}

void Player::update(double dt)
{
	int curX = m_rect.getPosition().x / 50;
	int curY = m_rect.getPosition().y / 50;

	std::cout << curX << ", " << curY << std::endl;
	m_heading.x = cos(m_rotation * DEG_TO_RAD);
	m_heading.y = sin(m_rotation * DEG_TO_RAD);
	m_rect.setPosition(m_rect.getPosition().x + m_heading.x * m_speed * (dt / 1000), m_rect.getPosition().y + m_heading.y* m_speed * (dt / 1000));
	m_rect.setRotation(m_rotation);

	//key presses 
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		decreaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		increaseRotation();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		increaseSpeed();
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		decreaseSpeed();
	}

	//looping screen 
	if (m_rect.getPosition().x > 1920)
	{
		m_rect.setPosition(-100, m_rect.getPosition().y);
	}
	if (m_rect.getPosition().x < -200)
	{
		m_rect.setPosition(1920, m_rect.getPosition().y);
	}
	if (m_rect.getPosition().y < -200)
	{
		m_rect.setPosition(m_rect.getPosition().x, 1080);
	}
	if (m_rect.getPosition().y > 1080)
	{
		m_rect.setPosition(m_rect.getPosition().x, 0);
	}
}

void Player::render(sf::RenderWindow & window)
{
	window.draw(m_rect);
}

void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 0;
	}
}

void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}

void Player::increaseSpeed()
{
	if (m_speed < MAX_SPEED)
	{
		m_speed += 1;
	}
}

void Player::decreaseSpeed()
{
	if (m_speed > 0)
	{
		m_speed -= 1;
	}
}

sf::Vector2f Player::getPos()
{
	return m_rect.getPosition();
}


void Player::setPosition(float x, float y)
{
	m_rect.setPosition(x, y);
}

sf::Vector2f Player::getVel()
{
	return m_velocity;
}