#ifndef KVK_LOGGER
#define KVK_LOGGER

#include <stdio.h>
#include <string>
#include "termcolor/termcolor.hpp"

namespace Kvejge
{
    enum LogType
    {
        NORMAL,
        WARNING,
        ERR,
        CRITICAL
    };
    class Logger
    {
    public:
        Logger() {}
        ~Logger() {}

        void log(std::string message, LogType logType = LogType::NORMAL)
        {
            switch (logType)
            {
            case LogType::WARNING:
                std::cout << termcolor::blue << message << termcolor::reset << std::endl;
                break;
            case LogType::ERR:
                std::cout << termcolor::red << termcolor::underline << message << termcolor::reset << std::endl;
                break;
            case LogType::CRITICAL:
                std::cout << termcolor::dark << termcolor::bold << termcolor::on_red << message << termcolor::reset << std::endl;
                break;
            default:
                std::cout << message << std::endl;
                break;
            }
        }
    };
} // namespace Kvejge

#endif