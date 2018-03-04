#pragma once

#include "PrerequisitesCore.h"
#include "IModule.h"

namespace ege
{
    enum class ComponentType
    {
        KEYBOARD, JOYPAD, MOUSE, INPUT_HANDLER
    };

    class IComponent
    {
    public:
        IComponent(ComponentType type);
        virtual ~IComponent() = 0;

        ComponentType GetType();

    protected:
        ComponentType _type;
    };
}
