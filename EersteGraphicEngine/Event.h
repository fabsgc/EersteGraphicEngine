#pragma once

namespace ege
{
    enum EventType
    {
        NONE
    };

    class Event
    {
    public:
        Event();
        Event(EventType type);
        ~Event() {};
        const EventType& GetType() const;

    private:
        EventType _type;
    };
}