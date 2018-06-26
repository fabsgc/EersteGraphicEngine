#include "FirstPersonCamera.h"
#include "InputHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    FirstPersonCamera::FirstPersonCamera()
        : FlyingCamera(CameraType::FirstPersonCamera)
    {
        _translationSpeed = 5.0f;
        _rotationSpeed = 1.0f;
    }

    FirstPersonCamera::~FirstPersonCamera()
    {
    }

    void FirstPersonCamera::Update()
    {
        float deltaTime = _time.GetFrameDelta();

        float walk = 0.0f;
        float strafe = 0.0f;
        float up = 0.0f;
        float zoom = 0.0f;
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

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            rotation.x = joypadRX;
            rotation.y = -joypadRY;

            if (fabs(joypadLY) > 0.0f)
                walk = joypadLY;
            if (fabs(joypadLX) > 0.0f)
                strafe = joypadLX;

            if (_joypad.GetThumbStick(JoypadThumbStickName::LEFT).Position > 0.0f)
                up = -_translationSpeed;
            else if (_joypad.GetThumbStick(JoypadThumbStickName::RIGHT).Position > 0.0f)
                up = _translationSpeed;
        }

        XMFLOAT2 relativeMovement = _mouse.GetRelativeMovement();
        rotation.y = relativeMovement.x;
        rotation.x = relativeMovement.y;

        if (fabs(rotation.x) > 0.0f)
            Pitch(rotation.x * _rotationSpeed * deltaTime);
        if (fabs(rotation.y) > 0.0f)
            Yaw(rotation.y * _rotationSpeed * deltaTime);

        if (fabs(walk) > 0.0f)
            Walk(walk * _translationSpeed * deltaTime);
        if (fabs(strafe) > 0.0f)
            Strafe(strafe * _translationSpeed * deltaTime, 0.0f, 0.0f);

        if (fabs(up) > 0.0f)
            Strafe(0.0, up * _translationSpeed * deltaTime, 0.0f);

        PerspectiveCamera::Update();
    }

    void FirstPersonCamera::Walk(float distance)
    {
        XMFLOAT3 oldPosition = _position;
        XMVECTOR s = XMVectorReplicate(distance);
        XMVECTOR l = XMLoadFloat3(&_look);
        XMVECTOR p = XMLoadFloat3(&_position);
        XMStoreFloat3(&_position, XMVectorMultiplyAdd(s, l, p));
        _position.y = oldPosition.y;

        _needUpdate = true;
    }

    void FirstPersonCamera::Strafe(XMFLOAT3 distance)
    {
        XMVECTOR right = XMLoadFloat3(&_right);
        XMVECTOR look = XMLoadFloat3(&_look);
        XMVECTOR up = XMLoadFloat3(&_up);
        XMVECTOR position = XMLoadFloat3(&_position);
        XMVECTOR movement = XMLoadFloat3(&distance);

        if (distance.y == 0.0f)
        {
            XMVECTOR strafe = right * XMVectorGetX(movement);
            position += strafe;

            XMVECTOR forward = look * XMVectorGetZ(movement);
            position += forward;

            XMStoreFloat3(&_position, position);
        }
        else
        {
            XMVECTOR climb = up * XMVectorGetY(movement);
            _position.y += XMVectorGetY(climb);
        }

        _needUpdate = true;
    }

    void FirstPersonCamera::Strafe(float x, float y, float z)
    {
        Strafe(XMFLOAT3(x, y, z));
    }
}