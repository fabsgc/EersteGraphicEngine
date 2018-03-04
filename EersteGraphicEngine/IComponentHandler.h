#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"

namespace ege
{
    class IComponentHandler
    {
    public:
        IComponentHandler() {}
        virtual ~IComponentHandler() = 0;

        void             InsertComponent(SPtr<IComponent> component);
        IComponent&      GetComponent(ComponentType type);
        SPtr<IComponent> GetComponentPtr(ComponentType type);

    private:
        std::map<ComponentType, SPtr<IComponent>> _components;
    };
}
