#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player(SDL_Texture & texture);
	~Player();
	void update(SDL_Event & event, double dt);
	void render(SDL_Renderer* renderer);
	void setPosition(float posX, float posY);
	void increaseRotation();
	void decreaseRotation();
	void increaseSpeed();
	void decreaseSpeed();
private:
	SDL_Rect m_image_hitbox;

	SDL_Rect screenRect;
	SDL_Rect imageRect;
	SDL_Point center;
	//SDL_Surface
	SDL_Surface * m_surface;
	SDL_Texture * m_image;
	std::pair<float, float> m_heading;
	std::pair<int, int> m_position;
	std::pair<float, float> m_velocity;
	std::pair<int, int> m_size;
	double static const DEG_TO_RAD;
	double m_rotation;
	double m_speed;
	double MAX_SPEED;

};

