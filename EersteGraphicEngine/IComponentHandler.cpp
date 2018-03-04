#include "IComponentHandler.h"

namespace ege
{
    IComponentHandler::~IComponentHandler()
    {
    }

    void IComponentHandler::InsertComponent(SPtr<IComponent> component)
    {
        auto inserted = _components.insert(std::make_pair(component->GetType(), component));
        EGE_ASSERT_ERROR(inserted.second, "A component with the same type already exists here");
    }

    IComponent& IComponentHandler::GetComponent(ComponentType type)
    {
        auto found = _components.find(type);
        EGE_ASSERT_ERROR((found != _components.end()), "No component of that type here");

        return *found->second;
    }

    SPtr<IComponent> IComponentHandler::GetComponentPtr(ComponentType type)
    {
        auto found = _components.find(type);
        EGE_ASSERT_ERROR((found != _components.end()), "No component of that type here");

        return found->second;
    }
}