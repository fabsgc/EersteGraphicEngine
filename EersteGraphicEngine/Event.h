#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class Event
    {
    public:
        Event(const String& data);
        ~Event() {};
        const String& GetName() const;
        void          Suscribe(std::function<void()> callback);
        void          Execute();
        bool          operator==(const String& name) const;

    private:
        String _name;
        std::vector<std::function<void()>> _callbacks;
    };
}