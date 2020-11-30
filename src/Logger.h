#ifndef GE_LOGGER
#define GE_LOGGER

#include <stdio.h>

namespace Kvejge
{
    class Logger
    {
    public:
        Logger() {}
        ~Logger() {}

        void logSomeStuff() { printf("Fuck you\n"); }
    };
} // namespace Kvejge

#endif