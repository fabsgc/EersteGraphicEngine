#include "Mouse.h"

namespace ege
{
    Mouse::Mouse()
        : IComponent(ComponentType::MOUSE)
        , _window(gWindow())
        , _position(XMFLOAT2(0.0f, 0.0f))
        , _oldPosition(XMFLOAT2(0.0f, 0.0f))
        , _mouseWheel(MouseWheelState::STATIC)
        , _relativeMovement(XMFLOAT2(0.0f, 0.0f))
    {}

    void Mouse::Update(MSG* message)
    {
        UpdatePosition(message);

        switch (message->message)
        {
        case WM_LBUTTONDOWN:
            UpdateState(MouseButtonName::LEFT, MouseButtonState::TRIGGERED);
            break;

        case WM_RBUTTONDOWN:
            UpdateState(MouseButtonName::RIGHT, MouseButtonState::TRIGGERED);
            break;

        case WM_MBUTTONDOWN:
            UpdateState(MouseButtonName::MIDDLE, MouseButtonState::TRIGGERED);
            break;

        case WM_LBUTTONUP:
            UpdateState(MouseButtonName::LEFT, MouseButtonState::RELEASED);
            break;

        case WM_RBUTTONUP:
            UpdateState(MouseButtonName::RIGHT, MouseButtonState::RELEASED);
            break;

        case WM_MBUTTONUP:
            UpdateState(MouseButtonName::MIDDLE, MouseButtonState::RELEASED);
            break;

        case WM_MOUSEHWHEEL:
        {
        }break;

        case WM_MOUSEWHEEL: 
        {
            if (((short)HIWORD(message->wParam)) / 120 > 0)
            {
                _mouseWheel = MouseWheelState::ROLL_UP;
            }
            else if (((short)HIWORD(message->wParam)) / 120 < 0)
            {
                _mouseWheel = MouseWheelState::ROLL_DOWN;
            }
            }break;
        }
    }

    void Mouse::ResetState()
    {
        _mouseWheel = MouseWheelState::STATIC;
        _relativeMovement = XMFLOAT2(0.0f, 0.0f);

    }

    void Mouse::UpdateState(const MouseButtonName& name, const MouseButtonState& state)
    {
        for (auto button = _mouseButtons.begin(); button != _mouseButtons.end(); button++)
        {
            if ((*button) == name)
            {
                (*button).State = state;
                (*button).Switched = MouseButtonSwitchedState::YES;
            }
        }
    }

    void Mouse::UpdateSwitched(MouseButton* button)
    {
        button->Switched = MouseButtonSwitchedState::NO;
    }

    const XMFLOAT2& Mouse::GetPosition() const
    {
        return _position;
    }

    const XMFLOAT2& Mouse::GetOldPosition() const
    {
        return _oldPosition;
    }

    MouseButtonState Mouse::GetState(const MouseButtonName& name) 
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), name) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == name)
                {
                    MouseButtonState state = it->State;
                    UpdateSwitched(&*it);
                    return state;
                }
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _mouseButtons.begin()->State;
    }

    MouseButtonState Mouse::GetState(const String& label) 
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), label) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == label)
                {
                    MouseButtonState state = it->State;
                    UpdateSwitched(&*it);
                    return state;
                }
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
        }

        return _mouseButtons.begin()->State;
    }

    MouseButton Mouse::GetMouseButton(const MouseButtonName& name)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), name) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == name)
                {
                    MouseButton mouse = *it;
                    UpdateSwitched(&*it);
                    return mouse;
                }
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_mouseButtons.begin();
    }

    MouseButton Mouse::GetMouseButton(const String& label)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), label) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == label)
                {
                    MouseButton mouse = *it;
                    UpdateSwitched(&*it);
                    return mouse;
                }
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
        }

        return *_mouseButtons.begin();
    }

    const MouseWheelState& Mouse::GetWheelState() const
    {
        return _mouseWheel;
    }

    const XMFLOAT2& Mouse::GetCentralPosition() const
    {
        return _centralPosition;
    }

    const XMFLOAT2& Mouse::GetCursorDistanceFromCenter() const
    {
        return _cursorDistanceFromCenter;
    }

    const XMFLOAT2& Mouse::GetRelativeMovement() const
    {
        return _relativeMovement;
    }

    void Mouse::SetRelativeMovement(const XMFLOAT2& relativeMovement)
    {
        _relativeMovement = relativeMovement;
    }

    void Mouse::OnStartUp()
    {
        _centralPosition.x = (float)_window.GetWindowWidth() / 2;
        _centralPosition.y = (float)_window.GetWindowHeight() / 2;

        _mouseButtons.push_back(MouseButton(MouseButtonName::LEFT));
        _mouseButtons.push_back(MouseButton(MouseButtonName::RIGHT));
        _mouseButtons.push_back(MouseButton(MouseButtonName::MIDDLE));
    }

    void Mouse::UpdatePosition(MSG* message)
    {
        _oldPosition = _position;

        _position.x = (float)GET_X_LPARAM(message->lParam);
        _position.y = (float)GET_Y_LPARAM(message->lParam);

        _centralPosition.x = (float)_window.GetWindowWidth() / 2;
        _centralPosition.y = (float)_window.GetWindowHeight() / 2;

        _cursorDistanceFromCenter.x = _position.x - _centralPosition.x;
        _cursorDistanceFromCenter.y = _position.y - _centralPosition.y;
    }

    Mouse& gMouse()
    {
        return static_cast<Mouse&>(Mouse::Instance());
    }

    SPtr<Mouse> gMousePtr()
    {
        return ege_shared_ptr(static_cast<Mouse*>(Mouse::InstancePtr()));
    }
}