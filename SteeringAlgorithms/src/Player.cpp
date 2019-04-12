#include "../Include/Headers/Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player(std::vector<Obstacle*>  obs) :
	m_position(0.0f, 0.0f),
	m_velocity(0.0f, 0.0f),
	size(100),
	m_rotation(0.0),
	m_speed(0.0),
	MAX_SPEED(150.0),
	m_obstacles(obs)
{
	if (!m_texture.loadFromFile("resources/assets/triangleOne.png")) {
		//do something
	}
	m_rect.setOrigin(m_position.x + 50.0f / 2, m_position.y + 25.0f / 2);
	m_rect.setTexture(&m_texture);
	m_rect.setSize(sf::Vector2f(50.0f, 25.0f));
	m_position = sf::Vector2f(900.0f, 500.0f);
	m_rect.setPosition(m_position);

	m_color = sf::Color::Red;
	m_rect.setFillColor(m_color);

	m_surround.setRadius(m_radius);
	m_surround.setPosition(0, 0);
	m_surround.setOrigin(m_surround.getRadius(), m_surround.getRadius());
	m_surround.setPosition(m_position);
	m_surround.setFillColor(sf::Color(0, 0, 0, 40));
}


Player::~Player()
{
}

/// <summary>
/// update the player position and key presses 
/// </summary>
/// <param name="dt">delta time</param>
void Player::update(double dt)
{
	int curX = m_rect.getPosition().x / 50.0f;
	int curY = m_rect.getPosition().y / 50.0f;

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

	m_surround.setPosition(m_rect.getPosition());
	obstacleCollision();

}

/// <summary>
/// render the player visuals
/// </summary>
/// <param name="window"></param>
void Player::render(sf::RenderWindow & window)
{
	if (m_visuals) {
		window.draw(m_surround);
	}
	window.draw(m_rect);
}

/// <summary>
/// incremts the rotation
/// </summary>
void Player::increaseRotation()
{
	m_rotation += 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 0;
	}
}
/// <summary>
/// decrements the rotation 
/// </summary>
void Player::decreaseRotation()
{
	m_rotation -= 1;
	if (m_rotation == 0.0)
	{
		m_rotation = 359.0;
	}
}
/// <summary>
/// increases the characetrs speed
/// </summary>
void Player::increaseSpeed()
{
	if (m_speed < MAX_SPEED)
	{
		m_speed += 1;
	}
}

/// <summary>
/// decreases the player speed
/// </summary>
void Player::decreaseSpeed()
{
	if (m_speed > 0)
	{
		m_speed -= 1;
	}
}

/// <summary>
/// returns the player positiojn 
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getPos()
{
	return m_rect.getPosition();
}

/// <summary>
/// sets the players position 
/// </summary>
/// <param name="pos"></param>
void Player::setPosition(sf::Vector2f pos)
{
	m_rect.setPosition(pos);
}

/// <summary>
/// returns the velocity 
/// </summary>
/// <returns></returns>
sf::Vector2f Player::getVel()
{
	return m_velocity;
}

/// <summary>
/// checks for collision between the player and obstacles
/// </summary>
void Player::obstacleCollision()
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		if (Math::circleCollision(m_rect.getPosition(), m_obstacles[i]->getPosition(), m_radius, m_obstacles[i]->getRadius()) && m_speed > 0)
		{
			m_speed = -20;
		}
	}
}

/// <summary>
/// resets the player
/// </summary>
void Player::reset() {
	m_speed = 0;
}