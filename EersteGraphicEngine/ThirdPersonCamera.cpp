#include "ThirdPersonCamera.h"
#include "InputHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

#include <algorithm>

namespace ege
{
    const float ThirdPersonCamera::DefaultZoomSpeed  = 12.0f;
    const float ThirdPersonCamera::DefaultRadius     = 64.0f;
    const float ThirdPersonCamera::DefaultStartAlpha = -XM_PIDIV2;
    const float ThirdPersonCamera::DefaultStartBeta  = MathUtility::G_PIDIV6;
    const float ThirdPersonCamera::DefaultMinZoom    = 1.00f;
    const float ThirdPersonCamera::DefaultMaxZoom    = 1024.0f;
    const XMFLOAT3 ThirdPersonCamera::DefaultTarget  = XMFLOAT3(0.0f, 0.0f, 0.0f);

    ThirdPersonCamera::ThirdPersonCamera()
        : PerspectiveCamera(CameraType::ThirdPersonCamera)
        , _zoomSpeed(DefaultZoomSpeed)
        , _radius(DefaultRadius)
        , _alpha(DefaultStartAlpha)
        , _beta(DefaultStartBeta)
        , _target(XMFLOAT3(0.0f, 8.0f, 0.0f))
        , _lastMousePosition(XMFLOAT2(1000.0f, 1000.0f))
    {
        _rotationSpeed = 1.0f;
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
        float deltaTime       = _time.GetFrameDelta();
        float speedModulation = (_radius > 16.0f) ? 1.0f : 0.5f;

        float walk   = 0.0f;
        float strafe = 0.0f;
        float up     = 0.0f;
        float zoom   = 0.0f;
        XMFLOAT2 rotation = XMFLOAT2(0.0f, 0.0f);

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            walk = _translationSpeed;
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            walk = -_translationSpeed;

        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            strafe = -_translationSpeed;
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            strafe = _translationSpeed;

        if (_inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            up = _translationSpeed;
        else if (_inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            up = -_translationSpeed;

        if (_inputHandler.GetState("ZOOM_UP").State == InputHandlerState::TRIGGERED)
            zoom = _zoomSpeed;
        else if (_inputHandler.GetState("ZOOM_DOWN").State == InputHandlerState::TRIGGERED)
            zoom = -_zoomSpeed;

        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 mousePosition = _mouse.GetPosition();
            XMFLOAT2 mouseOldPosition = _mouse.GetOldPosition();

            if (mousePosition.x != _lastMousePosition.x || mousePosition.y != _lastMousePosition.y)
            {
                XMFLOAT2 distance = XMFLOAT2(mousePosition.x - mouseOldPosition.x, mousePosition.y - mouseOldPosition.y);

                rotation.x = -distance.x;
                rotation.y = distance.y;

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
					walk = distance.y;
				if (abs(distance.x) > 0.0f)
					strafe = -distance.x;

				_lastMousePosition = mousePosition;
			}
		}

        MouseWheelState mouseWheelState = _mouse.GetWheelState();

        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            zoom = _zoomSpeed;
            break;

        case MouseWheelState::ROLL_DOWN:
            zoom = -_zoomSpeed;
            break;
        }

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            if (fabs(joypadLY) > 0.0f)
                walk = joypadLY;
            if (fabs(joypadLX) > 0.0f)
                strafe = joypadLX;

            rotation.x = -joypadRX;
            rotation.y = -joypadRY;
        }

        if (fabs(rotation.x) > 0.0f)
            Pitch(rotation.x * _rotationSpeed * deltaTime);
        if (fabs(rotation.y) > 0.0f)
            Yaw(rotation.y * _rotationSpeed * deltaTime);

        if (fabs(walk) > 0.0f)
            Walk(walk * _translationSpeed * deltaTime);
        if (fabs(strafe) > 0.0f)
            Strafe(strafe * _translationSpeed * deltaTime);

        if (fabs(up) > 0.0f)
            Up(up * _translationSpeed * deltaTime);

        if (abs(zoom) > 0.0f)
            Zoom(zoom * _zoomSpeed * deltaTime * speedModulation);

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
        _alpha = fmodf(_alpha + angle, XM_PI * 2.0f + 0.01f);

        _needUpdate = true;
    }

    void ThirdPersonCamera::Yaw(float angle)
    {
        _beta += angle;
        _beta = MathUtility::Clamp(_beta, -XM_PI / 2.0f + 0.01f, XM_PI / 2.0f - 0.01f);

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

    void ThirdPersonCamera::SetTarget(XMFLOAT3 target)
    {
        _target = target;
        _needUpdate = true;
    }

    void ThirdPersonCamera::SetRadius(float radius)
    {
        _radius = radius;
        _needUpdate = true;
    }

    void ThirdPersonCamera::SetAlpha(float alpha)
    {
        _alpha = alpha;
        _needUpdate = true;
    }

    void ThirdPersonCamera::SetBeta(float beta)
    {
        _beta = beta;
        _needUpdate = true;
    }

    void ThirdPersonCamera::SetZoomSpeed(float zoomSpeed)
    {
        _zoomSpeed = zoomSpeed;
    }

    XMFLOAT3 ThirdPersonCamera::GetTarget()
    {
        return _target;
    }
}