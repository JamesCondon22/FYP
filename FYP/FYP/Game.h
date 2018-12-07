#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>

#include "Player.h"

using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update(double dt);
	void render();
	void initialise();

	SDL_Texture* loadTexture(std::string file);
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	Player* m_player;

	

};



#endif // !GAME
