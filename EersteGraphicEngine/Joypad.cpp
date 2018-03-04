#include "Joypad.h"

namespace ege
{
    Joypad::Joypad()
        : IComponent(ComponentType::JOYPAD)
    {}

    void Joypad::Update(MSG* message, float deltaTime)
    {
    }

    void Joypad::UpdateState(JoypadButtonName name, JoypadButtonState state, double value)
    {
        for (auto button = _joypadButtons.begin(); button != _joypadButtons.end(); button++)
        {
            if ((*button).Name == name)
            {
                (*button).State = state;
                (*button).Value = value;
            }
        }
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

    void Joypad::OnStartUp()
    {
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::A));
    }

    void Joypad::OnShutDown()
    {
    }
}