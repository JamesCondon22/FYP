#include "Game.h"

Game::Game()
{
	m_window = SDL_CreateWindow("FYP", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1200, 700, SDL_WINDOW_OPENGL);
	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

	int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;

	if (IMG_Init(imgFlags) != imgFlags)
	{
		cout << "Error: " << IMG_GetError() << endl;
	}


	initialise();
}

Game::~Game()
{
}

void Game::run()
{
	const Uint32 fps = 60;
	const Uint32 minimumFrameTime = 1000 / fps;

	Uint32 frameTime;
	Uint32 lastFrameTime = 0;
	Uint32 deltaTime = 0;

	while (!exit) {

		processEvents();
		frameTime = SDL_GetTicks();

		deltaTime = frameTime - lastFrameTime;
		lastFrameTime = frameTime;

		update(deltaTime);
		render();

		if ((SDL_GetTicks() - frameTime) < minimumFrameTime)
			SDL_Delay(minimumFrameTime - (SDL_GetTicks() - frameTime));
	}

	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

void Game::processEvents()
{


	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			exit = true;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				exit = true;
			break;
		}
	}
}

void Game::update(double dt)
{
	m_player->update(event, dt);
}

void Game::render()
{
	if (m_renderer == nullptr)
	{
		SDL_Log("Could not create a renderer: %s", SDL_GetError());
	}
	
	SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
	SDL_RenderClear(m_renderer);
	m_player->render(m_renderer);
	SDL_RenderPresent(m_renderer);

}


void Game::initialise()
{
	m_player = new Player(*loadTexture("triangle.png"));
}

SDL_Texture* Game::loadTexture(std::string file)
{
	SDL_Texture* newTexture = NULL;

	SDL_Surface* loadedSurface = IMG_Load(file.c_str());

	if (loadedSurface == NULL) {
		printf("Unable to load image &s! SDL_image Error: %s\n", file.c_str(), IMG_GetError());
	}
	else {
		newTexture = SDL_CreateTextureFromSurface(m_renderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from &s! SDL_Error: %s\n", file.c_str(), SDL_GetError());
		}
		SDL_FreeSurface(loadedSurface);
	}
	return newTexture;
}

