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

    JoypadButtonState Joypad::GetState(JoypadButtonName name)
    {
        if (std::find(_joypadButtons.begin(), _joypadButtons.end(), name) != _joypadButtons.end())
        {
            for (auto _button : _joypadButtons)
            {
                if (_button.Name == name) return _button.State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _joypadButtons.begin()->State;
    }

    JoyStick& Joypad::GetJoyStick(JoypadStickName name)
    {
        if (std::find(_joysticks.begin(), _joysticks.end(), name) != _joysticks.end())
        {
            for (auto it = _joysticks.begin(); it != _joysticks.end(); it++)
            {
                if (it->Name == name) return *it;
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
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::A));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::B));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::X));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::Y));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::START));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::SELECT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LB));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RB));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::JOYSTICK_LEFT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::JOYSTICK_RIGHT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_LEFT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_RIGHT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_UP));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_DOWN));

        _joysticks.push_back(JoyStick(JoypadStickName::LEFT));
        _joysticks.push_back(JoyStick(JoypadStickName::RIGHT));
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