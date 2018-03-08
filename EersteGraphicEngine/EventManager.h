#pragma once

#include "PrerequisitesCore.h"
#include "IModule.h"
#include "Event.h"

namespace ege
{
    class EventManager : public IModule<EventManager>
    {
    public:
        EventManager();
        ~EventManager();

        void OnStartUp() override;
        void OnShutDown() override;

    private:

    };

    EventManager&      gEventManager();
    SPtr<EventManager> gEventManagerPtr();
}