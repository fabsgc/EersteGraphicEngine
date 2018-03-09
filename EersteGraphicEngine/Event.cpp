#include "Event.h"

namespace ege
{
    Event::Event(const String& name)
        : _name(name)
    {}

    const String& Event::GetName() const
    {
        return _name;
    }

    void Event::Suscribe(std::function<void()> callback)
    {
        _callbacks.push_back(callback);
    }

    void Event::Execute()
    {
        for (auto callbackIt = _callbacks.begin(); callbackIt != _callbacks.end(); callbackIt++)
        {
            (*callbackIt)();
        }
    }

    bool Event::operator==(const String& name) const
    {
        if (_name == name)
        {
            return true;
        }

        return false;
    }
}