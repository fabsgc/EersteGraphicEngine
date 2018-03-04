#include "IComponent.h"

namespace ege
{
    IComponent::IComponent(ComponentType type)
        : _type(type)
    {
    }

    IComponent::~IComponent()
    {
    }

    ComponentType IComponent::GetType()
    {
        return _type;
    }
}