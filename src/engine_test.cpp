#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>
#include <math.h>
#include <algorithm>

#include "Texture.h"
#include "TexturePack.h"
#include "TextureAnimation.h"
#include "Timer.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *window = NULL;
SDL_Renderer *renderer = NULL;
Texture foregroundTexture;
Texture backgroundTexture;
TexturePack texturepack;
Mix_Music *music = NULL;
TextureAnimation textureanim;

Uint8 modR, modG, modB;
Uint8 alphaTest = 255;
Uint8 cellIdTest = 0;

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

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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
	foregroundTexture.setKeyColor(0, 255, 255);
	backgroundTexture.setRenderer(renderer);
	texturepack.setRenderer(renderer);
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
	if (!texturepack.loadFromFile("resources/texturepack.png"))
	{
		printf("Failed to load texturepack!\n");
		return false;
	}
	if ((music = Mix_LoadMUS("resources/music.ogg")) == NULL)
	{
		printf("Failed to load music! SDL_mixer Error: %s\n", Mix_GetError());
		return false;
	}
	textureanim.setTexturePack(&texturepack);
	textureanim.setMinMaxCellIds(4, 7);
	textureanim.play(.1f);
	return true;
}

void exit()
{
	foregroundTexture.free();
	backgroundTexture.free();
	texturepack.free();
	SDL_DestroyRenderer(renderer);
	renderer = NULL;
	SDL_DestroyWindow(window);
	window = NULL;
	Mix_FreeMusic(music);
	music = NULL;

	Mix_Quit();
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
	Timer timer;
	while (!shouldQuit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				shouldQuit = true;
			}
			else if (e.type == SDL_KEYDOWN)
			{
				int incBy = 32;
				if (e.key.keysym.mod & (KMOD_LSHIFT | KMOD_RSHIFT) > 0)
					incBy = -32;

				switch (e.key.keysym.sym)
				{
				case SDLK_r:
					modR = std::clamp(modR + incBy, 0, 255);
					break;
				case SDLK_g:
					modG = std::clamp(modG + incBy, 0, 255);
					break;
				case SDLK_b:
					modB = std::clamp(modB + incBy, 0, 255);
					break;

				case SDLK_a:
					if (timer.isStarted())
						timer.stop();
					else
						timer.start();
					break;

				case SDLK_KP_PLUS:
					cellIdTest++;
					texturepack.setCellId(cellIdTest);
					break;
				case SDLK_KP_MINUS:
					cellIdTest--;
					texturepack.setCellId(cellIdTest);
					break;

				case SDLK_SPACE:
					if (Mix_PlayingMusic() == 0)
						Mix_PlayMusic(music, -1);
					else
					{
						if (Mix_PausedMusic() == 1)
							Mix_ResumeMusic();
						else
							Mix_PauseMusic();
					}
					break;
				case SDLK_ESCAPE:
					Mix_HaltMusic();
					break;
				}
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		backgroundTexture.render(0, 0);
		foregroundTexture.setModColor(modR, modG, modB);
		foregroundTexture.setAlpha(alphaTest);
		foregroundTexture.render(240, 190);
		textureanim.render(0, 0);

		texturepack.render(128, 128);

		alphaTest = (sin(timer.getTicks() / 200.f) / 2 + .5f) * 255;

		SDL_RenderPresent(renderer);
	}

	exit();
	return 0;
}