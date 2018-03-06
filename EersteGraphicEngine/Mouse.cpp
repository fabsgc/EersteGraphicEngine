#include "Mouse.h"

namespace ege
{
    Mouse::Mouse()
        : IComponent(ComponentType::MOUSE)
        , _window(gWindow())
        , _position(XMFLOAT2(0.0f, 0.0f))
    {}

    void Mouse::Update(MSG* message)
    {
        _position.x = (float)GET_X_LPARAM(message->lParam);
        _position.y = (float)GET_Y_LPARAM(message->lParam);

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
        }
    }

    void Mouse::UpdateState(MouseButtonName name, MouseButtonState state)
    {
        for (auto button = _mouseButtons.begin(); button != _mouseButtons.end(); button++)
        {
            if ((*button) == name)
            {
                (*button).State = state;
            }
        }
    }

    XMFLOAT2 Mouse::GetPosition()
    {
        return _position;
    }

    MouseButtonState& Mouse::GetState(const MouseButtonName& name)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), name) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == name) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _mouseButtons.begin()->State;
    }

    MouseButtonState& Mouse::GetState(const String& label)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), label) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == label) return it->State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
        }

        return _mouseButtons.begin()->State;
    }

    MouseButton& Mouse::GetMouseButton(const MouseButtonName& name)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), name) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == name) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return *_mouseButtons.begin();
    }

    MouseButton& Mouse::GetMouseButton(const String& label)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), label) != _mouseButtons.end())
        {
            for (auto it = _mouseButtons.begin(); it != _mouseButtons.end(); it++)
            {
                if (*it == label) return *it;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, ("No button with this name (" + label + ")"));
        }

        return *_mouseButtons.begin();
    }

    void Mouse::OnStartUp()
    {
        _mouseButtons.push_back(MouseButton(MouseButtonName::LEFT));
        _mouseButtons.push_back(MouseButton(MouseButtonName::RIGHT));
        _mouseButtons.push_back(MouseButton(MouseButtonName::MIDDLE));
    }

    void Mouse::OnShutDown()
    {
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