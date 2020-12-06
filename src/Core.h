#ifndef KVK_CORE
#define KVK_CORE

#include <SDL.h>
#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#endif
#include <string>
#include "Logger.h"
#include "EventHandler.h"

namespace Kvejge
{
    class Core
    {
    public:
        Core(int width = 640, int height = 480, std::string title = "Kvejge project");
        ~Core();
        void quit();

    private:
        SDL_Window *sdlWindow;
        SDL_Surface *sdlSurface;
        Logger *logger;
        EventHandler *ehandler;

        void mainLoop();
        bool shouldQuit;
    };
} // namespace Kvejge

#endif