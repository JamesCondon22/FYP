#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

class Player
{
public:
	Player();
	~Player();
	void update();
	void render(SDL_Renderer* renderer);
private:
	SDL_Rect m_image_hitbox;
	//SDL_Surface
	SDL_Surface * m_surface;
	SDL_Texture * m_image;
};

