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

        void        InsertComponent(IComponent& component);
        IComponent& GetComponent(ComponentType type);

    private:
        Map<ComponentType, IComponent*> _components;
    };
}
