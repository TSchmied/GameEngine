#include "EventHandler.h"

namespace Kvejge
{
    void EventHandler::update()
    {
        keysPressedStack.clear();
        keysReleasedStack.clear();
        mbPressedStack.clear();
        mbReleasedStack.clear();
        eventStack.clear();

        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            switch (e.type)
            {
            case SDL_KEYDOWN:
            {
                struct KeyboardEvent event;
                event.str = e.key.keysym.sym;
                event.type = KeyEventType::PRESS;
                keysPressedStack.push_back(event.str);
                keysHeldStack.push_back(event.str);
                break;
            }
            case SDL_KEYUP:
            {
                struct KeyboardEvent event;
                event.str = e.key.keysym.sym;
                event.type = KeyEventType::RELEASE;
                keysHeldStack.erase(std::remove(keysHeldStack.begin(), keysHeldStack.end(), event.str), keysHeldStack.end());
                keysReleasedStack.push_back(event.str);
                break;
            }
            case SDL_MOUSEBUTTONDOWN:
            {
                struct MouseEvent mevent;
                mevent.button = static_cast<MouseButton>(e.button.button);
                mevent.type = KeyEventType::PRESS;
                mbHeldStack.push_back(mevent.button);
                mbPressedStack.push_back(mevent.button);
                break;
            }
            case SDL_MOUSEBUTTONUP:
            {
                struct MouseEvent mevent;
                mevent.button = static_cast<MouseButton>(e.button.button);
                mevent.type = KeyEventType::RELEASE;
                mbHeldStack.erase(std::remove(mbHeldStack.begin(), mbHeldStack.end(), static_cast<MouseButton>(e.button.button)), mbHeldStack.end());
                mbReleasedStack.push_back(mevent.button);
                break;
            }
            default:
            {
                eventStack.push_back(e.type);
                // logger->log("Unknown event! SDL event type: " + std::to_string(e.type), LogType::WARNING);
                break;
            }
            }
        }
    }

    bool EventHandler::isKeyPressed(std::string keyString)
    {
        return (std::find(keysPressedStack.begin(), keysPressedStack.end(), keyString) != keysPressedStack.end());
    }
    bool EventHandler::isKeyHeld(std::string keyString)
    {
        return (std::find(keysHeldStack.begin(), keysHeldStack.end(), keyString) != keysHeldStack.end());
    }
    bool EventHandler::isKeyReleased(std::string keyString)
    {
        return (std::find(keysReleasedStack.begin(), keysReleasedStack.end(), keyString) != keysReleasedStack.end());
    }

    bool EventHandler::isMousePressed(MouseButton button)
    {
        return (std::find(mbPressedStack.begin(), mbPressedStack.end(), button) != mbPressedStack.end());
    }
    bool EventHandler::isMouseHeld(MouseButton button)
    {
        return (std::find(mbHeldStack.begin(), mbHeldStack.end(), button) != mbHeldStack.end());
    }
    bool EventHandler::isMouseReleased(MouseButton button)
    {
        return (std::find(mbReleasedStack.begin(), mbReleasedStack.end(), button) != mbReleasedStack.end());
    }

    bool EventHandler::hasEventHappened(Uint32 sdlEventType)
    {
        return (std::find(eventStack.begin(), eventStack.end(), sdlEventType) != eventStack.end());
    }
} // namespace Kvejge