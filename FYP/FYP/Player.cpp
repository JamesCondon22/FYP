#include "Player.h"



Player::Player()
{ 
	m_surface = IMG_Load("triangle.png");
	if (m_surface == nullptr) {
		std::cout << "IMG_Load: " << IMG_GetError() << "\n";
	}
	m_image_hitbox.x = 10;
	m_image_hitbox.y = 10;
	m_image_hitbox.w = 30;
	m_image_hitbox.h = 40;
}


Player::~Player()
{
}

void Player::update() {

}

void Player::render(SDL_Renderer* renderer) {
	m_image = SDL_CreateTextureFromSurface(renderer, m_surface);
	SDL_RenderCopy(renderer, m_image, nullptr, &m_image_hitbox);
	SDL_DestroyTexture(m_image);
}
