#include "FlyingCamera.h"
#include "InputHandler.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    FlyingCamera::FlyingCamera()
        : Camera(CameraType::ThirdPerson)
    {
    }

    FlyingCamera::FlyingCamera(CameraType type)
        : Camera(type)
    {
    }

    FlyingCamera::~FlyingCamera()
    {
    }

    void FlyingCamera::Update()
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
            MoveY(1.0f * deltaTime);
        else if (_inputHandler.GetState("GO_DOWN").State == InputHandlerState::TRIGGERED)
            MoveY(-1.0f * deltaTime);
        
        if (_mouse.GetState(MouseButtonName::LEFT) == MouseButtonState::TRIGGERED)
        {
            XMFLOAT2 cursorDistanceFromCenter = _mouse.GetCursorDistanceFromCenter();
            float angleY = cursorDistanceFromCenter.x * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleX = cursorDistanceFromCenter.y * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if (abs(angleX) > 0)
                Pitch(angleX);
            if (abs(angleY) > 0)
                Yaw(angleY);
        }

        if (_joypad.IsConnected())
        {
            float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX * 200.0f;
            float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY * 200.0f;

            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            float angleX = -joypadRY * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;
            float angleY = joypadRX * _rotationSpeed * deltaTime * MathUtility::G_PI / 180.0f;

            if(abs(joypadLY) > 0.0f)
                Walk(joypadLY * _translationSpeed * deltaTime);
            if(abs(joypadLX) > 0.0f)
                MoveX(joypadLX * _translationSpeed * deltaTime);

            if (abs(angleX) > 0.0f)
                Pitch(angleX);
            if (abs(angleY) > 0.0f)
                Yaw(angleY);

            if (_joypad.GetThumbStick(JoypadThumbStickName::LEFT).Position > 0.0f)
                MoveY(_translationSpeed * deltaTime);
            else if (_joypad.GetThumbStick(JoypadThumbStickName::RIGHT).Position > 0.0f)
                MoveY(_translationSpeed * deltaTime);
        }

        Camera::Update();
    }

    void FlyingCamera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        XMVECTOR R = XMLoadFloat3(&_right);
        XMVECTOR U = XMLoadFloat3(&_up);
        XMVECTOR L = XMLoadFloat3(&_look);
        XMVECTOR P = XMLoadFloat3(&_position);

        // Keep camera's axes orthogonal to each other and of unit length.
        L = XMVector3Normalize(L);
        U = XMVector3Normalize(XMVector3Cross(L, R));

        // U, L already ortho-normal, so no need to normalize cross product.
        R = XMVector3Cross(U, L);

        // Fill in the view matrix entries.
        float x = -XMVectorGetX(XMVector3Dot(P, R));
        float y = -XMVectorGetX(XMVector3Dot(P, U));
        float z = -XMVectorGetX(XMVector3Dot(P, L));

        XMStoreFloat3(&_right, R);
        XMStoreFloat3(&_up, U);
        XMStoreFloat3(&_look, L);

        _view(0, 0) = _right.x;
        _view(1, 0) = _right.y;
        _view(2, 0) = _right.z;
        _view(3, 0) = x;

        _view(0, 1) = _up.x;
        _view(1, 1) = _up.y;
        _view(2, 1) = _up.z;
        _view(3, 1) = y;

        _view(0, 2) = _look.x;
        _view(1, 2) = _look.y;
        _view(2, 2) = _look.z;
        _view(3, 2) = z;

        _view(0, 3) = 0.0f;
        _view(1, 3) = 0.0f;
        _view(2, 3) = 0.0f;
        _view(3, 3) = 1.0f;

        XMStoreFloat4x4(&_projection, XMMatrixPerspectiveFovLH(_fov, windowWidth / (FLOAT)windowHeight, _nearZ, _farZ));
    }

    void FlyingCamera::Walk(float distance)
    {
        XMVECTOR s = XMVectorReplicate(distance);
        XMVECTOR l = XMLoadFloat3(&_look);
        XMVECTOR p = XMLoadFloat3(&_position);
        XMStoreFloat3(&_position, XMVectorMultiplyAdd(s, l, p));

        _needUpdate = true;
    }

    void FlyingCamera::Move(XMFLOAT3 distance)
    {
        XMVECTOR right = XMLoadFloat3(&_right);
        XMVECTOR look = XMLoadFloat3(&_look);
        XMVECTOR up = XMLoadFloat3(&_up);
        XMVECTOR position = XMLoadFloat3(&_position);
        XMVECTOR movement = XMLoadFloat3(&distance);

        XMVECTOR strafe = right * XMVectorGetX(movement);
        position += strafe;

        XMVECTOR climb = up * XMVectorGetY(movement);
        position += climb;

        XMVECTOR forward = look * XMVectorGetZ(movement);
        position += forward;

        XMStoreFloat3(&_position, position);

        _needUpdate = true;
    }

    void FlyingCamera::Move(float x, float y, float z)
    {
        Move(XMFLOAT3(x, y, z));
    }

    void FlyingCamera::MoveX(float x)
    {
        Move(x, 0.0f, 0.0f);
    }

    void FlyingCamera::MoveY(float y)
    {
        Move(0.0f, y, 0.0f);
    }

    void FlyingCamera::MoveZ(float z)
    {
        Move(0.0f, 0.0f, z);
    }

    void FlyingCamera::Pitch(float angle)
    {
        XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_right), angle);

        XMVECTOR up = XMVector3TransformCoord(XMLoadFloat3(&_up), T);
        XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_look), T);

        XMStoreFloat3(&_up, up);
        XMStoreFloat3(&_look, look);

        _needUpdate = true;
    }

    void FlyingCamera::Roll(float angle)
    {
        XMMATRIX T = XMMatrixRotationAxis(XMLoadFloat3(&_look), angle);

        XMVECTOR right = XMVector3TransformCoord(XMLoadFloat3(&_right), T);
        XMVECTOR up = XMVector3TransformCoord(XMLoadFloat3(&_up), T);

        XMStoreFloat3(&_right, right);
        XMStoreFloat3(&_up, up);

        _needUpdate = true;
    }

    void FlyingCamera::Yaw(float angle)
    {
        XMMATRIX T = XMMatrixRotationY(angle);

        XMVECTOR right = XMVector3TransformCoord(XMLoadFloat3(&_right), T);
        XMVECTOR look = XMVector3TransformCoord(XMLoadFloat3(&_look), T);

        XMStoreFloat3(&_right, right);
        XMStoreFloat3(&_look, look);

        _needUpdate = true;
    }
}