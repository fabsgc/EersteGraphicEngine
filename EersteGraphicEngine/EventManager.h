#pragma once

#include "PrerequisitesCore.h"
#include "Event.h"

namespace ege
{
    class EventManager : public IModule<EventManager>
    {
    public:
        EventManager() {};
        ~EventManager() {};

        void Create(const String& name);
        void Suscribe(const String& name, std::function<void()> callback);
        void Execute(const String& name);
        void Delete(const String& name);

        void OnStartUp() override {};
        void OnShutDown() override {};

    private:
        const bool Exist(const String& name) const;

    private:
        std::vector<SPtr<Event>> _events;
    };

    EventManager&      gEventManager();
    SPtr<EventManager> gEventManagerPtr();
}