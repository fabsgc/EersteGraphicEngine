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
        InputHandler& inputHandler = gInputHandler();
        Joypad& joypad = gJoypad();
        Mouse& mouse = gMouse();
        Time& time = gTime();

        float deltaTime = time.GetFrameDelta();

        if (inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Walk(_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Walk(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            MoveZ(1.0f * deltaTime);
        if (inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            MoveZ(-1.0f * deltaTime);

        XMFLOAT2 relativeMovement = mouse.GetRelativeMovement();

        float angleX = relativeMovement.x * _rotationSpeed * deltaTime;
        float angleY = relativeMovement.y * _rotationSpeed * deltaTime * 2.0f;

        if (abs(angleY) > 0.001f)
            Pitch(angleY);
        if (abs(angleX) > 0.001f)
            Yaw(angleX);

        if (joypad.IsConnected())
        {
            float joypadRX = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

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
        }

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

        ComputeProjectionMatrix();
    }
}