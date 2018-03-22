#pragma once

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
        virtual ~IComponent() = 0 {};

        const ComponentType GetType() const;

    protected:
        ComponentType _type;
    };
}
