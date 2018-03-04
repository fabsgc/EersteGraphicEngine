#pragma once

#include "PrerequisitesCore.h"
#include "IModule.h"

namespace ege
{
    enum class ComponentType
    {
        KEYBOARD, JOYPAD, MOUSE, INPUT_HANDLER
    };

    class IComponent : public IModule<CoreApplication>
    {
    public:
        IComponent(ComponentType type);
        virtual ~IComponent() = 0;

        template<class T = IComponent>
        static void StartUp(ComponentType type)
        {
            IModule::StartUp<T>(type);
        }

        ComponentType GetType();

    protected:
        ComponentType _type;
    };
}
