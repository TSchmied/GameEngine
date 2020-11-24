#include <SDL.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const char* HELLOWORLD_IMAGE = "resources/helloworld.bmp";

SDL_Window* window = NULL;
SDL_Surface* screenSurface = NULL;
SDL_Surface* helloWorld = NULL;

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
	screenSurface = SDL_GetWindowSurface(window);

	return true;
}

bool loadMedia()
{
	helloWorld = SDL_LoadBMP(HELLOWORLD_IMAGE);
	if (helloWorld == NULL)
	{
		printf("Unable to load image %s! SDL_Error: %s\n", HELLOWORLD_IMAGE, SDL_GetError());
		return false;
	}

	return true;
}

void exit()
{
	SDL_FreeSurface(helloWorld);
	helloWorld = NULL;
	SDL_DestroyWindow(window);
	window = NULL;

	SDL_Quit();
}

int main( int argc, char* args[] )
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
	SDL_BlitSurface(helloWorld, NULL, screenSurface, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);

	exit();
	return 0;
}