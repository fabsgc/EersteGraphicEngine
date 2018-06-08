#include "ThirdPersonCamera.h"
#include "InputHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

#include <algorithm>

namespace ege
{
    const float ThirdPersonCamera::DefaultMinZoom = 0.75f;
    const float ThirdPersonCamera::DefaultMaxZoom = 0.75f;

    ThirdPersonCamera::ThirdPersonCamera()
        : Camera()
        , _alpha(0.0f)
        , _beta(0.0f)
        , _radius(10.0f)
        , _target(XMFLOAT3(0.0f, 0.0f, 0.0f))
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
    }

    ThirdPersonCamera::~ThirdPersonCamera()
    {
    }

    void ThirdPersonCamera::Initialise()
    {
        LookAt(XMFLOAT3(0.0f, 0.0f, -6.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 1.0f));
        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Update()
    {
        InputHandler& inputHandler = gInputHandler();
        Joypad& joypad = gJoypad();
        Mouse& mouse = gMouse();
        Time& time = gTime();

        float deltaTime = time.GetFrameDelta();
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        if (inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Walk(_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Walk(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            Strafe(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            Strafe(_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            Zoom(-deltaTime * 5.0f);
        if (inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            Zoom(deltaTime * 5.0f);

        if (mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);

                float angleY = -distance.x * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 75.0f;
                float angleX = distance.y * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 75.0f;

                Pitch(angleX);
                Yaw(angleY);
                    
                _lastMousePosition = mousePosition;
            }
        }

        MouseWheelState mouseWheelState = mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            Zoom(-deltaTime * 15.0f);
            break;

        case MouseWheelState::ROLL_DOWN:
            Zoom(deltaTime * 15.0f);
            break;
        }

        if (joypad.IsConnected())
        {
            float joypadRX = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleY = -joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if (abs(joypadLY) > 0.0f)
                Walk(joypadLY * _translationSpeed * deltaTime);
            if (abs(joypadLX) > 0.0f)
                Strafe(joypadLX * _translationSpeed * deltaTime);

            if (abs(angleX) > 0.0f)
                Pitch(angleX);
            if (abs(angleY) > 0.0f)
                Yaw(angleY);
        }

        Camera::Update();
    }

    void ThirdPersonCamera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        float sideRadius = _radius * cos(_beta);
        float height = _radius * sin(_beta);

        _position = XMFLOAT3(
            _target.x + sideRadius * cos(_alpha),
            _target.y + height,
            _target.z + sideRadius * sin(_alpha)
        );

        XMVECTOR P = XMLoadFloat3(&_position);
        XMVECTOR T = XMLoadFloat3(&_target);

        XMFLOAT3 unity = XMFLOAT3(0.0f, 1.0f, 0.0f);
        XMMATRIX view = XMMatrixLookAtLH(P, T, XMLoadFloat3(&unity));

        XMStoreFloat4x4(&_view, view);

        _right = XMFLOAT3(_view._11, _view._21, _view._31);
        XMVECTOR R = XMLoadFloat3(&_right);
        R = XMVector3Normalize(R);
        XMStoreFloat3(&_right, R);

        _look = XMFLOAT3(_view._13, _view._23, _view._33);
        XMVECTOR L = XMLoadFloat3(&_look);
        L = XMVector3Normalize(L);
        XMStoreFloat3(&_look, L);

        XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(_fov, windowWidth / (FLOAT)windowHeight, _nearZ, _farZ));
    }

    void ThirdPersonCamera::LookAt(XMFLOAT3 position, XMFLOAT3 target, XMFLOAT3 up)
    {
        _position = position;
        _target = target;
        _up = up;        

        XMVECTOR _R = XMLoadFloat3(&_right);
        XMVECTOR _U = XMLoadFloat3(&_up);
        XMVECTOR _L = XMLoadFloat3(&_look);
        XMVECTOR _P = XMLoadFloat3(&_position);
        XMVECTOR _T = XMLoadFloat3(&_target);

        _L = XMVector3Normalize(_T - _P);
        _R = XMVector3Normalize(XMVector3Cross(_U, _L));
        _U = XMVector3Cross(_L, _R);

        XMVECTOR length = XMVector3Length(_T - _P);
        XMStoreFloat(&_radius, length);

        XMStoreFloat3(&_right, _R);
        XMStoreFloat3(&_up, _U);
        XMStoreFloat3(&_look, _L);
    }

    void ThirdPersonCamera::Pitch(float angle)
    {
        _beta += angle;
        _beta = MathUtility::Clamp(_beta, - XM_PI / 2.0f + 0.01f, XM_PI / 2.0f - 0.01f);

        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Yaw(float angle)
    {
        _alpha = fmodf(_alpha + angle, XM_PI * 2.0f);

        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Strafe(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(_right.x, 0.0f, _right.z))) * distance;
        XMStoreFloat3(&_target, T);

        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Walk(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(_look.x, 0, _look.z))) * distance;
        XMStoreFloat3(&_target, T);

        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Up(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(0.0f, _look.y, 0.0f))) * distance;
        XMStoreFloat3(&_target, T);

        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Zoom(float zoom)
    {
        _radius += zoom;
        _radius = MathUtility::Clamp(_radius, 0.75f, 128.0f);

        ComputeProjectionMatrix();
    }
}