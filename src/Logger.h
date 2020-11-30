#ifndef GE_LOGGER
#define GE_LOGGER

#include <stdio.h>

namespace GameEngine
{
    class Logger
    {
    public:
        Logger() {}
        ~Logger() {}

        void logSomeStuff() { printf("Fuck you\n"); }
    };
} // namespace GameEngine

#endif