#include "ThirdPersonCamera.h"
#include "InputHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

#include <algorithm>

namespace ege
{
    const float ThirdPersonCamera::DefaultMinZoom = 0.25f;
    const float ThirdPersonCamera::DefaultMaxZoom = 1024.0f;

    ThirdPersonCamera::ThirdPersonCamera()
        : PerspectiveCamera(CameraType::ThirdPersonCamera)
        , _alpha(0.0f)
        , _beta(0.4f)
        , _radius(64.0f)
        , _target(XMFLOAT3(0.0f, 8.0f, 0.0f))
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
    }

    ThirdPersonCamera::~ThirdPersonCamera()
    {
    }

    void ThirdPersonCamera::Initialise()
    {
        ComputeProjectionMatrix();
    }

    void ThirdPersonCamera::Update()
    {
        float deltaTime = _time.GetFrameDelta();
        float speedModulation = (_radius / 10.0f > 2.0f) ? _radius / 10.0f : 2.0f;

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Walk(_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Walk(-_translationSpeed * deltaTime * speedModulation);

        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            Strafe(-_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            Strafe(_translationSpeed * deltaTime * speedModulation);

        if (_inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            Up(_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            Up(-_translationSpeed * deltaTime * speedModulation);

        if (_inputHandler.GetState("ZOOM_UP").State == InputHandlerState::TRIGGERED)
            Zoom(_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("ZOOM_DOWN").State == InputHandlerState::TRIGGERED)
            Zoom(-_translationSpeed * deltaTime * speedModulation);

        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = _mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);

                float angleX = -distance.x * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 75.0f;
                float angleY = distance.y * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 75.0f;
                
                Pitch(angleY);
                Yaw(angleX);
                    
                _lastMousePosition = mousePosition;
            }
        }

		if (_mouse.GetState(MouseButtonName::RIGHT) == MouseButtonState::TRIGGERED)
		{
			XMFLOAT2 mousePosition = _mouse.GetPosition();
			XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

			if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
			{
				XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);

				if (abs(distance.y) > 0.0f)
					Walk(distance.y * deltaTime * speedModulation);
				if (abs(distance.x) > 0.0f)
					Strafe(-distance.x * deltaTime * speedModulation);

				_lastMousePosition = mousePosition;
			}
		}

        MouseWheelState mouseWheelState = _mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            Zoom(deltaTime * _translationSpeed * speedModulation * 3.0f);
            break;

        case MouseWheelState::ROLL_DOWN:
            Zoom(-deltaTime * _translationSpeed * speedModulation * 3.0f);
            break;
        }

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = -joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 2.0f;
            float angleY = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f * 2.0f;

            if (abs(joypadLY) > 0.0f)
                Walk(joypadLY * _translationSpeed * deltaTime *  speedModulation);
            if (abs(joypadLX) > 0.0f)
                Strafe(joypadLX * _translationSpeed * deltaTime * speedModulation);

            if (abs(angleY) > 0.0f)
                Pitch(angleY);
            if (abs(angleX) > 0.0f)
                Yaw(angleX);
        }

        PerspectiveCamera::Update();
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

        _needUpdate = true;
    }

    void ThirdPersonCamera::Yaw(float angle)
    {
        _alpha = fmodf(_alpha + angle, XM_PI * 2.0f);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Strafe(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(_right.x, 0.0f, _right.z))) * distance;
        XMStoreFloat3(&_target, T);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Walk(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(_look.x, 0, _look.z))) * distance;
        XMStoreFloat3(&_target, T);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Up(float distance)
    {
        XMVECTOR T = XMLoadFloat3(&_target);
        T += XMVector3Normalize(XMLoadFloat3(&XMFLOAT3(0.0f, _up.y, 0.0f))) * distance;
        XMStoreFloat3(&_target, T);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Zoom(float zoom)
    {
        _radius -= zoom;
        _radius = MathUtility::Clamp(_radius, DefaultMinZoom, DefaultMaxZoom);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Move(XMVECTOR movement)
    {

    }

    void ThirdPersonCamera::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {

    }

    void ThirdPersonCamera::Rotate(XMVECTOR eulerAngles)
    {

    }
}