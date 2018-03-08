#include "EventManager.h"

namespace ege
{
    EventManager::EventManager()
    {

    }

    EventManager::~EventManager() 
    {

    }

    void EventManager::OnStartUp()
    {

    }

    void EventManager::OnShutDown()
    {

    }

    EventManager& gEventManager()
    {
        return EventManager::Instance();
    }

    SPtr<EventManager> gEventManagerPtr()
    {
        return ege_shared_ptr(static_cast<EventManager*>(EventManager::InstancePtr()));
    }
}