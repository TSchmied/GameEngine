#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif

#include "Logger.h"

SDL_Window *window;
SDL_Surface *surface;

void gameloop()
{
    SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 255, 0, 103));
    SDL_UpdateWindowSurface(window);
}

int main(int argc, char *args[])
{
    Kvejge::Logger logger;
    logger.logSomeStuff();

    SDL_Init(SDL_INIT_VIDEO);
    window = SDL_CreateWindow("KVEJGE TEST", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    surface = SDL_GetWindowSurface(window);

    #ifdef __EMSCRIPTEN__
    emscripten_set_main_loop(gameloop, 0, 1);
    #else
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
        gameloop();
    }
    #endif

    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}