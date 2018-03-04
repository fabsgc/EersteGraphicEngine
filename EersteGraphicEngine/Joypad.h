#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"
#include "Window.h"

namespace ege
{
    enum class JoypadButtonName
    {
        A, B, X, Y,
        START, SELECT,
        LB, LT, RT, RB,
        JOYSTICK_LEFT, JOYSTICK_RIGHT,
        ARROW_LEFT, ARROW_RIGHT, ARROW_UP, ARROW_DOWN
    };

    enum class JoypadButtonState
    {
        TRIGGERED, RELEASED
    };

    struct JoypadButton
    {
        JoypadButtonName  Name;
        JoypadButtonState State;
        double            Value;

        JoypadButton(JoypadButtonName name)
            : Name(name)
            , Value(0.0)
            , State(JoypadButtonState::RELEASED)
        {}

        bool operator==(JoypadButtonName name) const
        {
            return name == Name;
        }
    };

    class Joypad : public IComponent {
    public:
        Joypad();
        ~Joypad() {}
        void              Update(MSG* message, float deltaTime);
        JoypadButtonState GetState(JoypadButtonName name);

    private:
        void             UpdateState(JoypadButtonName name, JoypadButtonState state, double value = 0.0);
        void             OnStartUp() override;
        void             OnShutDown() override;

    private:
        Vector<JoypadButton> _joypadButtons;
    };
}