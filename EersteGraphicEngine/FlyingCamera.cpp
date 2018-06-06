#include "FlyingCamera.h"
#include "InputHandler.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    FlyingCamera::FlyingCamera()
        : Camera()
    {
    }

    FlyingCamera::~FlyingCamera()
    {
    }

    void FlyingCamera::Update()
    {
        InputHandler& inputHandler = gInputHandler();
        Joypad& joypad             = gJoypad();
        Mouse& mouse               = gMouse();
        Time& time                 = gTime();

        float deltaTime = time.GetFrameDelta();

        if (inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
            MoveZ(1.0f * deltaTime);
        if (inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            MoveZ(-1.0f * deltaTime);
        if (inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
            Fly(_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
            Fly(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
            MoveX(-_translationSpeed * deltaTime);
        if (inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
            MoveX(_translationSpeed * deltaTime);
        
        if (mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 cursorDistanceFromCenter = mouse.GetCursorDistanceFromCenter();
            float angleY = cursorDistanceFromCenter.x * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleX = cursorDistanceFromCenter.y * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            Pitch(angleX);
            Yaw(angleY);
        }

        if (joypad.IsConnected())
        {
            float joypadRX = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 200.0f;
            float joypadRY = (float)joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 200.0f;

            float joypadLX = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleY = joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if(abs(joypadLY) > 0.0f)
                Fly(joypadLY * _translationSpeed * deltaTime);
            if(abs(joypadLX) > 0.0f)
                MoveX(joypadLX * _translationSpeed * deltaTime);

            if (abs(angleX) > 0.0f)
                Pitch(angleX);
            if (abs(angleY) > 0.0f)
                Yaw(angleY);
        }

        Camera::Update();
    }

    void FlyingCamera::Fly(float distance)
    {
        XMVECTOR s = XMVectorReplicate(distance);
        XMVECTOR l = XMLoadFloat3(&_look);
        XMVECTOR p = XMLoadFloat3(&_position);
        XMStoreFloat3(&_position, XMVectorMultiplyAdd(s, l, p));

        ComputeProjectionMatrix();
    }
}