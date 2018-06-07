#include "ThirdPersonCamera.h"
#include "Window.h"

namespace ege
{
    ThirdPersonCamera::ThirdPersonCamera()
        : Camera()
    {
    }

    ThirdPersonCamera::~ThirdPersonCamera()
    {
    }

    void ThirdPersonCamera::Update()
    {
        Time& time = gTime();
        float deltaTime = time.GetFrameDelta();
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        XMVECTOR quaternion = XMQuaternionRotationRollPitchYaw(0.005f, 0.0f, 0.0f);
        XMVECTOR position = XMLoadFloat3(&_position);

        XMMATRIX translation0 = XMMatrixTranslationFromVector(-position);
        XMMATRIX rotation = XMMatrixRotationQuaternion(XMQuaternionInverse(quaternion));
        XMMATRIX translation1 = XMMatrixTranslationFromVector(position);

        XMMATRIX view = XMLoadFloat4x4(&_view);

        view *= translation1 * rotation * translation0;

        XMMATRIX worldInverse = XMMatrixInverse(nullptr, view);
        XMFLOAT4X4 wordinv;
        XMStoreFloat4x4(&wordinv, worldInverse);
        _position.x = wordinv._41;
        _position.y = wordinv._42;
        _position.z = wordinv._43;

        XMStoreFloat3(&_position, position);
        XMStoreFloat4x4(&_view, view);

        Camera::Update();
    }
}