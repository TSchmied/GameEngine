#include "Core.h"

namespace Kvejge
{
    Core::Core(int width, int height, std::string title)
    {
        logger = new Logger();
        ehandler = new EventHandler(logger);
        logger->log("This is a warning", LogType::WARNING);
        logger->log("This is normal");
        SDL_Init(SDL_INIT_VIDEO);
        sdlWindow = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
        sdlSurface = SDL_GetWindowSurface(sdlWindow);

#ifdef __EMSCRIPTEN__
        emscripten_set_main_loop(Core::mainLoop, 0, 1);
#else
        bool shouldQuit = false;
        while (!shouldQuit)
        {
            shouldQuit = Core::mainLoop();
        }
#endif
    }
    Core::~Core()
    {
        delete logger;
        delete ehandler;
        SDL_DestroyWindow(sdlWindow);
        SDL_FreeSurface(sdlSurface);
        SDL_Quit();
    }

    bool Core::mainLoop()
    {
        ehandler->update();
        SDL_FillRect(sdlSurface, NULL, SDL_MapRGB(sdlSurface->format, 255, 0, 103));
        SDL_UpdateWindowSurface(sdlWindow);
        if (ehandler->isKeyPressed("e") || ehandler->hasEventHappened(SDL_QUIT))
            return true;
        return false;
    }
} // namespace Kvejge