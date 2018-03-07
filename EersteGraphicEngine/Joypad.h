#pragma once

#include "PrerequisitesCore.h"
#include "IComponent.h"
#include "IModule.h"
#include "Window.h"
#include "Time.h"

namespace ege
{
    enum class JoypadButtonName
    {
        A, B, X, Y,
        START, BACK,
        LB, LS, RB, RS,
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

    enum class JoypadThumbStickName
    {
        LEFT, RIGHT
    };

    struct JoypadButton
    {
        JoypadButtonName  Name;
        String            Label;
        JoypadButtonState State;
        WORD              Value;

        JoypadButton(const JoypadButtonName& name, const String& label, UINT value)
            : Name(name)
            , Label(label)
            , Value(value)
            , State(JoypadButtonState::RELEASED)
        {}

        bool operator==(const JoypadButton& button) const
        {
            return button.Name == Name;
        }

        bool operator==(const JoypadButtonName& name) const
        {
            return name == Name;
        }

        bool operator==(const String& label) const
        {
            return label == Label;
        }
    };

    struct JoyStick
    {
        JoypadStickName Name;
        String          Label;
        UINT            Value;
        double          AxisX;
        double          AxisY;

        JoyStick(const JoypadStickName& name, const String& label)
            : Name(name)
            , Label(label)
            , AxisX(0.0)
            , AxisY(0.0)
        {}

        bool operator==(const JoyStick& joystick) const
        {
            return joystick.Name == Name;
        }

        bool operator==(const JoypadStickName& name) const
        {
            return name == Name;
        }

        bool operator==(const String& label) const
        {
            return label == Label;
        }
    };

    struct ThumbStick
    {
        JoypadThumbStickName Name;
        String               Label;
        double               Position;

        ThumbStick(const JoypadThumbStickName& name, const String& label)
            : Name(name)
            , Label(label)
            , Position(0.0)
        {}

        bool operator==(const ThumbStick& thumbStick) const
        {
            return thumbStick.Name == Name;
        }

        bool operator==(const JoypadThumbStickName& name) const
        {
            return name == Name;
        }

        bool operator==(const String& label) const
        {
            return label == Label;
        }
    };

    class Joypad : public IModule<Joypad>, public IComponent {
    public:
        Joypad();
        ~Joypad() {}
        void                     Update();
        bool                     IsConnected();
        const JoypadButtonState& GetState(const JoypadButtonName& name) const;
        const JoypadButtonState& GetState(const String& label) const;
        JoypadButton&            GetJoypadButton(const JoypadButtonName& name);
        JoypadButton&            GetJoypadButton(const String& label);
        JoyStick&                GetJoyStick(const JoypadStickName& name);
        JoyStick&                GetJoyStick(const String& label);
        ThumbStick&              GetThumbStick(const JoypadThumbStickName& name);
        ThumbStick&               GetThumbStick(const String& label);

    private:
        void               OnStartUp() override;
        void               OnShutDown() override {};
        void               CheckJoypadConnected();

    private:
        static float DEAD_ZONE_X;
        static float DEAD_ZONE_Y;

    private:
        bool                 _isConnected;
        Vector<JoypadButton> _joypadButtons;
        Vector<JoyStick>     _joysticks;
        Vector<ThumbStick>   _thumbSticks;

        XINPUT_STATE         _state;
        XINPUT_STATE         _oldState;

        float                _lastUpdateState;
    };

    Joypad&      gJoypad();
    SPtr<Joypad> gJoypadPtr();
}