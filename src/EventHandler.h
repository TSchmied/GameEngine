#ifndef KVK_EVENT_HANDLER
#define KVK_EVENT_HANDLER

#include <SDL.h>
#include <string>
#include <vector>
#include <algorithm>
#include "Logger.h"

namespace Kvejge
{
    enum KeyEventType
    {
        PRESS,
        RELEASE
    };
    enum MouseButton
    {
        LEFT = SDL_BUTTON_LEFT,
        MIDDLE = SDL_BUTTON_MIDDLE,
        RIGHT = SDL_BUTTON_RIGHT
    };
    struct Event
    {
    };
    struct KeyEvent : Event
    {
        KeyEventType type;
    };
    struct KeyboardEvent : KeyEvent
    {
        std::string str;
    };
    struct MouseEvent : KeyEvent
    {
        MouseButton button;
    };

    class EventHandler
    {
    public:
        EventHandler(Logger *sysLogger) { logger = sysLogger; }
        ~EventHandler() {}

        void update();

        bool isKeyPressed(std::string keyString);
        bool isKeyHeld(std::string keyString);
        bool isKeyReleased(std::string keyString);

        bool isMousePressed(MouseButton button);
        bool isMouseHeld(MouseButton button);
        bool isMouseReleased(MouseButton button);

        bool hasEventHappened(Uint32 sdlEventType);

    private:
        Logger *logger;
        std::vector<Uint32> eventStack;
        std::vector<std::string> keysPressedStack;
        std::vector<std::string> keysHeldStack;
        std::vector<std::string> keysReleasedStack;
        std::vector<MouseButton> mbPressedStack;
        std::vector<MouseButton> mbHeldStack;
        std::vector<MouseButton> mbReleasedStack;
    };
} // namespace Kvejge

#endif