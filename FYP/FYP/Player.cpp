#include "Player.h"


double const Player::DEG_TO_RAD = 3.14 / 180.0f;
Player::Player(SDL_Texture & texture) :
	m_position(0,0),
	m_velocity(0,0),
	MAX_SPEED(350),
	m_image(&texture),
	m_size(100,100)
{ 
	
	screenRect = { 0,0,1200,700 };
	imageRect = { m_position.first,m_position.second,m_size.first, m_size.second };
	SDL_QueryTexture(m_image, nullptr, nullptr, &m_size.first, &m_size.second);
	center.x = imageRect.w / 2;
	center.y = imageRect.h / 2;
}


Player::~Player()
{
}

void Player::update(SDL_Event & event, double dt) {
	
	m_heading.first = cos(m_rotation * DEG_TO_RAD);
	m_heading.second = cos(m_rotation * DEG_TO_RAD);
	setPosition(imageRect.x + m_heading.first * m_speed * (dt / 1000), imageRect.y + m_heading.second * m_speed * (dt / 1000));
	
	std::cout << m_rotation << std::endl;
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			decreaseRotation();
			break;
		case SDLK_RIGHT:
			increaseRotation();
			break;
		case SDLK_UP:
			increaseSpeed();
			break;
		case SDLK_DOWN:
			decreaseSpeed();
			break;
		}
	}
}

void Player::setPosition(float x, float y)
{
	imageRect.x = x;
	imageRect.y = y;
	//std::cout
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
void Player::render(SDL_Renderer* renderer) {
	SDL_RenderCopyEx(renderer, m_image, &screenRect, &imageRect, m_rotation, &center,SDL_FLIP_NONE);
}
