#include "Joypad.h"

namespace ege
{
    float Joypad::DEAD_ZONE_X = 0.2f;
    float Joypad::DEAD_ZONE_Y = 0.2f;

    Joypad::Joypad()
        : IComponent(ComponentType::JOYPAD)
        , _isConnected(false)
        , _lastUpdateState(0)
    {}

    void Joypad::Update()
    {
        if (_isConnected)
        {
            _lastUpdateState += gTime().GetFrameDelta();

            if (_lastUpdateState > 0.1f)
            {
                _lastUpdateState = 0;
                CheckJoypadConnected();

                if (_isConnected)
                {
                    float normLX = fmaxf(-1, (float)_state.Gamepad.sThumbLX / 32767);
                    float normLY = fmaxf(-1, (float)_state.Gamepad.sThumbLY / 32767);
                    float normRX = fmaxf(-1, (float)_state.Gamepad.sThumbRX / 32767);
                    float normRY = fmaxf(-1, (float)_state.Gamepad.sThumbRY / 32767);

                    _joysticks[0].AxisX = (abs(normLX) < DEAD_ZONE_X ? 0 : normLX);
                    _joysticks[0].AxisY = (abs(normLY) < DEAD_ZONE_Y ? 0 : normLY);
                    _joysticks[1].AxisX = (abs(normRX) < DEAD_ZONE_X ? 0 : normRX);
                    _joysticks[1].AxisY = (abs(normRY) < DEAD_ZONE_Y ? 0 : normRY);

                    _thumbSticks[0].Position = (float)_state.Gamepad.bLeftTrigger / 255;
                    _thumbSticks[1].Position = (float)_state.Gamepad.bRightTrigger / 255;

                    if (_oldState.Gamepad.wButtons != _state.Gamepad.wButtons)
                    {
                        for (auto itButtons = _joypadButtons.begin(); itButtons != _joypadButtons.end(); itButtons++)
                        {
                            if ((_state.Gamepad.wButtons & itButtons->Value) != 0)
                            {
                                itButtons->State = JoypadButtonState::TRIGGERED;
                            }
                            else
                            {
                                itButtons->State = JoypadButtonState::RELEASED;
                            }
                        }
                    }
                }
            }
        }
    }

    bool Joypad::IsConnected()
    {
        return _isConnected;
    }

    const JoypadButtonState& Joypad::GetState(const JoypadButtonName& name) const
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

    const JoypadButtonState& Joypad::GetState(const String& label) const
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
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
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
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
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
            EGE_ASSERT_ERROR(false, "No joystick with this name");
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
            EGE_ASSERT_ERROR(false, ("No joystick with this name (" + label + ")"));
        }

        return *_joysticks.begin();
    }

    ThumbStick& Joypad::GetThumbStick(const JoypadThumbStickName& name)
    {
        if (std::find(_thumbSticks.begin(), _thumbSticks.end(), name) != _thumbSticks.end())
        {
            for (auto it = _thumbSticks.begin(); it != _thumbSticks.end(); it++)
            {
                if (*it == name) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No joystick with this name");
        }

        return *_thumbSticks.begin();
    }

    ThumbStick& Joypad::GetThumbStick(const String& label)
    {
        if (std::find(_thumbSticks.begin(), _thumbSticks.end(), label) != _thumbSticks.end())
        {
            for (auto it = _thumbSticks.begin(); it != _thumbSticks.end(); it++)
            {
                if (*it == label) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("No joystick with this name (" + label + ")"));
        }

        return *_thumbSticks.begin();
    }

    void Joypad::OnStartUp()
    {
        CheckJoypadConnected();

        _joypadButtons.push_back(JoypadButton(JoypadButtonName::A, "A", XINPUT_GAMEPAD_A));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::B, "B", XINPUT_GAMEPAD_B));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::X, "X", XINPUT_GAMEPAD_X));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::Y, "Y", XINPUT_GAMEPAD_Y));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::START, "START", XINPUT_GAMEPAD_START));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::BACK, "BACK", XINPUT_GAMEPAD_BACK));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LB, "LB", XINPUT_GAMEPAD_LEFT_SHOULDER));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::LS, "LT", XINPUT_GAMEPAD_LEFT_THUMB));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RB, "RB", XINPUT_GAMEPAD_RIGHT_SHOULDER));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::RS, "RT", XINPUT_GAMEPAD_RIGHT_THUMB));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_LEFT, "ARROW_LEFT", XINPUT_GAMEPAD_DPAD_LEFT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_RIGHT, "ARROW_RIGHT", XINPUT_GAMEPAD_DPAD_RIGHT));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_UP, "ARROW_UP", XINPUT_GAMEPAD_DPAD_UP));
        _joypadButtons.push_back(JoypadButton(JoypadButtonName::ARROW_DOWN, "ARROW_DOWN", XINPUT_GAMEPAD_DPAD_DOWN));

        _joysticks.push_back(JoyStick(JoypadStickName::LEFT, "LEFT"));
        _joysticks.push_back(JoyStick(JoypadStickName::RIGHT, "RIGHT"));

        _thumbSticks.push_back(ThumbStick(JoypadThumbStickName::LEFT, "LEFT"));
        _thumbSticks.push_back(ThumbStick(JoypadThumbStickName::RIGHT, "RIGHT"));
    }

    void Joypad::CheckJoypadConnected()
    {
        DWORD dwResult;
        _oldState = _state;

        ZeroMemory(&_state, sizeof(XINPUT_STATE));
        dwResult = XInputGetState(0, &_state);

        if (dwResult == ERROR_SUCCESS)
        {
            _isConnected = true;
        }
        else
        {
            _isConnected = false;
        }
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