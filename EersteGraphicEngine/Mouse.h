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
        String           Label;
        MouseButtonState State;

        MouseButton(MouseButtonName name)
            : Name(name)
            , State(MouseButtonState::RELEASED)
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
        void              Update(MSG* message);
        XMFLOAT2          GetPosition();
        MouseButtonState& GetState(const MouseButtonName& name);
        MouseButtonState& GetState(const String& label);
        MouseButton&      GetMouseButton(const MouseButtonName& name);
        MouseButton&      GetMouseButton(const String& label);

    private:
        void              UpdateState(MouseButtonName name, MouseButtonState state);
        void              OnStartUp() override;
        void              OnShutDown() override;

    private:
        Window&             _window;
        XMFLOAT2            _position;
        Vector<MouseButton> _mouseButtons;
    };

    Mouse&      gMouse();
    SPtr<Mouse> gMousePtr();
}