#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    enum EventType
    {
        NONE, CUSTOM
    };

    class Event
    {
    public:
        Event();
        Event(EventType type);
        Event(EventType type, const String& data);
        ~Event() {};
        const EventType& GetType() const;
        const String& GetData() const;

    private:
        EventType _type;
        String    _data;
    };
}