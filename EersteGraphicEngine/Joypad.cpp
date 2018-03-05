#include "Joypad.h"

namespace ege
{
    Joypad::Joypad()
        : IComponent(ComponentType::JOYPAD)
        , _isConnected(false)
    {}

    void Joypad::Update()
    {
        //TODO
    }

    bool Joypad::IsConnected()
    {
        return _isConnected;
    }

    void Joypad::UpdateState(JoypadButton* button)
    {
        //TODO
    }

    void Joypad::UpdateState(JoyStick* stick)
    {
        //TODO
    }

    JoypadButtonState& Joypad::GetState(const JoypadButtonName& name)
    {
        if (std::find(_joypadButtons.begin(), _joypadButtons.end(), name) != _joypadButtons.end())
        {
            for (auto it = _joypadButtons.begin(); it != _joypadButtons.end(); it++)
            {
                if (*it == name) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _joypadButtons.begin()->State;
    }

    JoypadButtonState& Joypad::GetState(const String& label)
    {
        if (std::find(_joypadButtons.begin(), _joypadButtons.end(), label) != _joypadButtons.end())
        {
            for (auto it = _joypadButtons.begin(); it != _joypadButtons.end(); it++)
            {
                if (*it == label) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _joypadButtons.begin()->State;
    }

    JoypadButton& Joypad::GetJoypadButton(const JoypadButtonName& name)
    {
        if (std::find(_joypadButtons.begin(), _joypadButtons.end(), name) != _joypadButtons.end())
        {
            for (auto it = _joypadButtons.begin(); it != _joypadButtons.end(); it++)
            {
                if (*it == name) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_joypadButtons.begin();
    }

    JoypadButton& Joypad::GetJoypadButton(const String& label)
    {
        if (std::find(_joypadButtons.begin(), _joypadButtons.end(), label) != _joypadButtons.end())
        {
            for (auto it = _joypadButtons.begin(); it != _joypadButtons.end(); it++)
            {
                if (*it == label) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_joypadButtons.begin();
    }

    JoyStick& Joypad::GetJoyStick(const JoypadStickName& name)
    {
        if (std::find(_joysticks.begin(), _joysticks.end(), name) != _joysticks.end())
        {
            for (auto it = _joysticks.begin(); it != _joysticks.end(); it++)
            {
                if (*it == name) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_joysticks.begin();
    }

    JoyStick& Joypad::GetJoyStick(const String& label)
    {
        if (std::find(_joysticks.begin(), _joysticks.end(), label) != _joysticks.end())
        {
            for (auto it = _joysticks.begin(); it != _joysticks.end(); it++)
            {
                if (*it == label) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_joysticks.begin();
    }

    void Joypad::OnStartUp()
    {
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::A, "A"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::B, "B"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::X, "X"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::Y, "Y"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::START, "START"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::SELECT, "SELECT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LB, "LB"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LT, "LT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RB, "RB"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RT, "RT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::JOYSTICK_LEFT, "JOYSTICK_LEFT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::JOYSTICK_RIGHT, "JOYSTICK_RIGHT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_LEFT, "ARROW_LEFT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_RIGHT, "ARROW_RIGHT"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_UP, "ARROW_UP"));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_DOWN, "ARROW_DOWN"));

        _joysticks.push_back(JoyStick(JoypadStickName::LEFT, "LEFT"));
        _joysticks.push_back(JoyStick(JoypadStickName::RIGHT, "RIGHT"));
    }

    void Joypad::OnShutDown()
    {
    }

    Joypad& gJoypad()
    {
        return static_cast<Joypad&>(Joypad::Instance());
    }

    SPtr<Joypad> gJoypadPtr()
    {
        return ege_shared_ptr(static_cast<Joypad*>(Joypad::InstancePtr()));
    }
}