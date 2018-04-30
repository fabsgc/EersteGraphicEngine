#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"
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

    enum class MouseButtonSwitchedState
    {
        YES, NO
    };

    enum class MouseWheelState
    {
        ROLL_UP, ROLL_DOWN, STATIC
    };

    struct MouseButton
    {
        MouseButtonName  Name;
        String           Label;
        MouseButtonState State;
        MouseButtonSwitchedState Switched;

        MouseButton(MouseButtonName name)
            : Name(name)
            , State(MouseButtonState::RELEASED)
            , Switched(MouseButtonSwitchedState::NO)
        {}

        bool operator==(const MouseButton& mouse) const
        {
            return mouse.Name == Name;
        }

        bool operator==(const MouseButtonName& name) const 
        {
            return name == Name;
        }

        bool operator==(const String& label) const
        {
            return label == Label;
        }
    };

    class Mouse : public IModule<Mouse>, public IComponent {
    public:
        Mouse();
        ~Mouse() {}
        void                   Update(MSG* message);
        void                   ResetState();
        XMFLOAT2               GetPosition();
        MouseButtonState       GetState(const MouseButtonName& name);
        MouseButtonState       GetState(const String& label);
        MouseButton            GetMouseButton(const MouseButtonName& name);
        MouseButton            GetMouseButton(const String& label);
        const MouseWheelState& GetWheelState() const;

    private:
        void UpdateState(const MouseButtonName& name, const MouseButtonState& state);
        void UpdateSwitched(MouseButton* button);
        void OnStartUp() override;
        void OnShutDown() override {};

    private:
        Window&             _window;
        XMFLOAT2            _position;
        Vector<MouseButton> _mouseButtons;
        MouseWheelState     _mouseWheel;
    };

    Mouse&      gMouse();
    SPtr<Mouse> gMousePtr();
}