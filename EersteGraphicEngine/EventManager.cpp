#include "EventManager.h"

namespace ege
{
    void EventManager::Create(const String& name)
    {
        if (Exist(name))
        {
            EGE_ASSERT_ERROR(false, ("The event \"" + name + "\" already exists"));
        }

        _events.push_back(ege_shared_ptr(new Event(name)));
    }

    void EventManager::Suscribe(const String& name, std::function<void()> callback)
    {
        if (!Exist(name))
        {
            EGE_ASSERT_ERROR(false, ("The event \"" + name + "\" does not exist"));
        }

        for (auto eventIt = _events.begin(); eventIt != _events.end(); eventIt++)
        {
            if (**eventIt == name)
            {
                (*eventIt)->Suscribe(callback);
                break;
            }
        }
    }

    void EventManager::Execute(const String& name)
    {
        if (!Exist(name))
        {
            EGE_ASSERT_ERROR(false, ("The event \"" + name + "\" does not exist"));
        }

        for (auto eventIt = _events.begin(); eventIt != _events.end(); eventIt++)
        {
            if (**eventIt == name)
            {
                (*eventIt)->Execute();
                break;
            }
        }
    }

    void EventManager::Delete(const String& name)
    {
        for (auto eventIt = _events.begin(); eventIt != _events.end(); eventIt++)
        {
            if (**eventIt == name)
            {
                _events.erase(eventIt);
                break;
            }
        }
    }

    const bool EventManager::Exist(const String& name) const
    {
        for (auto event : _events)
        {
            if (*event == name)
            {
                return true;
            }
        }

        return false;
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