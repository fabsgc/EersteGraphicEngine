#include "Event.h"

namespace ege
{
    Event::Event()
        : _type(EventType::NONE)
    {}

    Event::Event(EventType type)
        : _type(type)
    {}

    const EventType& Event::GetType() const
    {
        return _type;
    }
}