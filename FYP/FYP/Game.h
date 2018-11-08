#ifndef GAME
#define GAME

#include <SDL.h>
#include <SDL_timer.h>
#include <SDL_image.h>
#include <stdlib.h>
#include <iostream>


using namespace std;

class Game {

public:
	Game();
	~Game();

	void run();

private:

	void processEvents();
	void update();
	void render();
	void initialise();

	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Event event;
	bool exit;

	

};



#endif // !GAME
