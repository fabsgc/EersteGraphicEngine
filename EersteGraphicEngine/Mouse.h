#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"
#include "IModule.h"
#include "Window.h"

namespace ege
{
    enum class MouseButtonName
    {
        LEFT, RIGHT, MIDDLE
    };

    enum class MouseButtonState
    {
        TRIGGERED, RELEASED
    };

    struct MouseButton
    {
        MouseButtonName  Name;
        MouseButtonState State;

        MouseButton(MouseButtonName name)
            : Name(name)
            , State(MouseButtonState::RELEASED)
        {}

        bool operator==(const MouseButtonName& name) const 
        {
            return name == Name;
        }

        bool operator==(const MouseButton& mouse) const
        {
            return mouse.Name == Name;
        }
    };

    class Mouse : public IModule<Mouse>, public IComponent {
    public:
        Mouse();
        ~Mouse() {}
        void             Update(MSG* message, float deltaTime);
        XMFLOAT2         GetPosition();
        MouseButtonState GetState(MouseButtonName name);

    private:
        void             UpdateState(MouseButtonName name, MouseButtonState state);
        void             OnStartUp() override;
        void             OnShutDown() override;

    private:
        Window&             _window;
        XMFLOAT2            _position;
        Vector<MouseButton> _mouseButtons;
    };

    Mouse&      gMouse();
    SPtr<Mouse> gMousePtr();
}