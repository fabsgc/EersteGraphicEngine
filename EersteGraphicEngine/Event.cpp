#include "Event.h"

namespace ege
{
    Event::Event()
        : _type(EventType::NONE)
        , _data("")
    {}

    Event::Event(EventType type)
        : _type(type)
        , _data("")
    {}

    Event::Event(EventType type, const String& data)
        : _type(type)
        , _data(data)
    {}

    const EventType& Event::GetType() const
    {
        return _type;
    }

    const String& Event::GetData() const
    {
        return _data;
    }
}