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
    }

    FirstPersonCamera::~FirstPersonCamera()
    {
    }

    void FirstPersonCamera::Update()
    {
        /*float deltaTime = _time.GetFrameDelta();
        float speedModulation = 2.0f;

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Walk(_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Walk(-_translationSpeed * deltaTime * speedModulation);
        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime * speedModulation);
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime * speedModulation);
        if (_inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            Strafe(0.0f, _translationSpeed * deltaTime * speedModulation, 0.0f);
        else if (_inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            Strafe(0.0f, -_translationSpeed * deltaTime * speedModulation, 0.0f);

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleY = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if (abs(joypadLY) > 0.0f)
                Walk(joypadLY * _translationSpeed * deltaTime * speedModulation);
            if (abs(joypadLX) > 0.0f)
                MoveX(joypadLX * _translationSpeed * deltaTime * speedModulation);

            if (abs(angleY) > 0.0f)
                Pitch(angleY);
            if (abs(angleX) > 0.0f)
                Yaw(angleX);

            if (_joypad.GetThumbStick(JoypadThumbStickName::LEFT).Position > 0.0f)
                MoveY(-_translationSpeed * deltaTime * speedModulation);
            else if (_joypad.GetThumbStick(JoypadThumbStickName::RIGHT).Position > 0.0f)
                MoveY(_translationSpeed * deltaTime * speedModulation);
        }

        XMFLOAT2 relativeMovement = _mouse.GetRelativeMovement();
        float angleX = relativeMovement.x * _rotationSpeed * deltaTime;
        float angleY = relativeMovement.y * _rotationSpeed * deltaTime;

        if (abs(angleY) > 0.001f)
            Pitch(angleY);
        if (abs(angleX) > 0.001f)
            Yaw(angleX);*/

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

    void FirstPersonCamera::Strafe(float x, float y, float z)
    {
        Strafe(XMFLOAT3(x, y, z));
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

    void FirstPersonCamera::Move(XMVECTOR movement)
    {}

    void FirstPersonCamera::Rotate(XMVECTOR origin, XMVECTOR eulerAngles)
    {}

    void FirstPersonCamera::Rotate(XMVECTOR eulerAngles)
    {}
}