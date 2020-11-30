#include "Timer.h"

Timer::Timer()
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::start()
{
    started = true;
    paused = false;
    startTicks = SDL_GetTicks();
    pausedTicks = 0;
}

void Timer::stop()
{
    started = false;
    paused = false;
    startTicks = 0;
    pausedTicks = 0;
}

void Timer::pause()
{
    if (started && !paused)
    {
        paused = true;
        pausedTicks = SDL_GetTicks() - startTicks;
        startTicks = 0;
    }
}

void Timer::unpause()
{
    if (started && paused)
    {
        paused = false;
        startTicks = SDL_GetTicks() - pausedTicks;
        pausedTicks = 0;
    }
}

Uint32 Timer::getTicks()
{
    if (started)
    {
        if (paused)
            return pausedTicks;
        else
            return SDL_GetTicks() - startTicks;
    }
    return 0;
}