#include "IComponent.h"

namespace ege
{
    IComponent::IComponent(ComponentType type)
        : _type(type)
    {}

    const ComponentType IComponent::GetType() const
    {
        return _type;
    }
}