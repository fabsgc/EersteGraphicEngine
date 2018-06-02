#include "FlyingCamera.h"
#include "InputHandler.h"
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
        Mouse& mouse               = gMouse();
        Time& time                 = gTime();

        float deltaTime = time.GetFrameDelta();
        XMFLOAT2 cursorDistanceFromCenter = mouse.GetCursorDistanceFromCenter();

        float angleY = cursorDistanceFromCenter.x * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
        float angleX = cursorDistanceFromCenter.y * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
        
        Pitch(angleX);
        Yaw(angleY);

        if (inputHandler.GetState("GO_UP").State == InputHandlerState::TRIGGERED)
        {
            MoveZ(_translationSpeed * deltaTime);
        }

        if (inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
        {
            MoveZ(-_translationSpeed * deltaTime);
        }

        if (inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
        {
            Fly(_translationSpeed * deltaTime);
        }

        if (inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
        {
            Fly(-_translationSpeed * deltaTime);
        }

        if (inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
        {
            MoveX(-_translationSpeed * deltaTime);
        }

        if (inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
        {
            MoveX(_translationSpeed * deltaTime);
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