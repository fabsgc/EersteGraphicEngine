#include "FirstPersonCamera.h"
#include "InputHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    FirstPersonCamera::FirstPersonCamera()
        : FlyingCamera()
    {
    }

    FirstPersonCamera::~FirstPersonCamera()
    {
    }

    void FirstPersonCamera::Update()
    {
        float deltaTime = _time.GetFrameDelta();

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Walk(_translationSpeed * deltaTime);
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Walk(-_translationSpeed * deltaTime);
        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime);
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime);
        if (_inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            MoveY(_translationSpeed * deltaTime);
        else if (_inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            MoveY(-_translationSpeed * deltaTime);

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleY = joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if (abs(joypadLY) > 0.0f)
                Walk(joypadLY * _translationSpeed * deltaTime);
            if (abs(joypadLX) > 0.0f)
                MoveX(joypadLX * _translationSpeed * deltaTime);

            if (abs(angleX) > 0.0f)
                Pitch(angleX);
            if (abs(angleY) > 0.0f)
                Yaw(angleY);

            if (_joypad.GetThumbStick(JoypadThumbStickName::LEFT).Position > 0.0f)
                MoveY(-_translationSpeed * deltaTime);
            else if (_joypad.GetThumbStick(JoypadThumbStickName::RIGHT).Position > 0.0f)
                MoveY(_translationSpeed * deltaTime);
        }

        XMFLOAT2 relativeMovement = _mouse.GetRelativeMovement();
        /*float angleX = relativeMovement.x * _rotationSpeed * deltaTime;
        float angleY = relativeMovement.y * _rotationSpeed * deltaTime * 2.0f;

        if (abs(angleY) > 0.001f)
            Pitch(angleY);
        if (abs(angleX) > 0.001f)
            Yaw(angleX);*/

        std::cout << relativeMovement.x << "/" << relativeMovement.y << std::endl;

        Camera::Update();
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

    void FirstPersonCamera::Move(XMFLOAT3 distance)
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
}