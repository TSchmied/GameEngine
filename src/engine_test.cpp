#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>

#include "Texture/Texture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Texture foregroundTexture;
Texture backgroundTexture;

bool init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	window = SDL_CreateWindow("GameEngine v0.1", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

	int imgFlags = IMG_INIT_JPG;
	if (!(IMG_Init(imgFlags) & imgFlags))
	{
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		return false;
	}

	return true;
}

SDL_Texture *loadTexture(std::string path)
{
	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", path.c_str(), IMG_GetError());
		return NULL;
	}
	if ((newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface)) == NULL)
	{
		printf("Unable to create texture from %s! SDL_Error: %s\n", path.c_str(), SDL_GetError());
	}
	SDL_FreeSurface(loadedSurface);
	return newTexture;
}

bool loadMedia()
{
	foregroundTexture.setRenderer(renderer);
	backgroundTexture.setRenderer(renderer);
	if (!foregroundTexture.loadFromFile("resources/texture.png"))
	{
		printf("Failed to load texture image!\n");
		return false;
	}
	if (!backgroundTexture.loadFromFile("resources/background.jpg"))
	{
		printf("Failed to load texture image!\n");
		return false;
	}
	return true;
}

void exit()
{
	foregroundTexture.free();
	backgroundTexture.free();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *args[])
{
	if (!init())
	{
		printf("Failed to initialize!\n");
		return -1;
	}
	if (!loadMedia())
	{
		printf("Failed to load media!\n");
		return -1;
	}

	bool shouldQuit = false;
	SDL_Event e;
	while (!shouldQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				shouldQuit = true;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		backgroundTexture.render(0, 0);
		foregroundTexture.render(240, 190);

		SDL_RenderPresent(renderer);
	}

	exit();
	return 0;
}