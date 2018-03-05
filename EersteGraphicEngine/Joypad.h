#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"
#include "IModule.h"
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

    enum class JoypadStickName
    {
        LEFT, RIGHT
    };

    struct JoypadButton
    {
        JoypadButtonName  Name;
        JoypadButtonState State;
        UINT              Value;

        JoypadButton(JoypadButtonName name)
            : Name(name)
            , Value(0)
            , State(JoypadButtonState::RELEASED)
        {}

        bool operator==(const JoypadButtonName& name) const
        {
            return name == Name;
        }

        bool operator==(const JoypadButton& button) const
        {
            return button.Name == Name;
        }
    };

    struct JoyStick
    {
        JoypadStickName Name;
        double          AxisX;
        double          AxisY;

        JoyStick(JoypadStickName name)
            : Name(name)
            , AxisX(0.0)
            , AxisY(0.0)
        {}

        bool operator==(const JoypadStickName& name) const
        {
            return name == Name;
        }

        bool operator==(const JoyStick& joystick) const
        {
            return joystick.Name == Name;
        }
    };

    class Joypad : public IModule<Joypad>, public IComponent {
    public:
        Joypad();
        ~Joypad() {}
        void              Update(float deltaTime);
        bool              IsConnected();
        JoypadButtonState GetState(JoypadButtonName name);
        JoyStick&         GetJoyStick(JoypadStickName name);

    private:
        void             UpdateState(JoypadButton* button);
        void             UpdateState(JoyStick* stick);
        void             OnStartUp() override;
        void             OnShutDown() override;

    private:
        bool                 _isConnected;
        Vector<JoypadButton> _joypadButtons;
        Vector<JoyStick>     _joysticks;
    };

    Joypad&      gJoypad();
    SPtr<Joypad> gJoypadPtr();
}