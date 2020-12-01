#include <SDL.h>

#include "Logger.h"

int main(int argc, char *args[])
{
    Kvejge::Logger logger;
    logger.logSomeStuff();

    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = SDL_CreateWindow("KVEJGE TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    SDL_Surface *surface = SDL_GetWindowSurface(window);

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
        SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 103));
        SDL_UpdateWindowSurface(window);
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}