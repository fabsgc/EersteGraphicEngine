#include "Mouse.h"

namespace ege
{
    Mouse::Mouse()
        : IComponent(ComponentType::MOUSE)
        , _window(gWindow())
        , _position(XMFLOAT2(0.0f, 0.0f))
    {}

    void Mouse::Update(MSG* message, float deltaTime)
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
            if ((*button).Name == name)
            {
                (*button).State = state;
            }
        }
    }

    XMFLOAT2 Mouse::GetPosition()
    {
        return _position;
    }

    MouseButtonState Mouse::GetState(MouseButtonName name)
    {
        if (std::find(_mouseButtons.begin(), _mouseButtons.end(), name) != _mouseButtons.end())
        {
            for (auto _button : _mouseButtons)
            {
                if (_button.Name == name) return _button.State;
            }
        }
        else
        {
            EGE_ASSERT_ERROR(false, "No button with this name");
        }

        return _mouseButtons.begin()->State;
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
}