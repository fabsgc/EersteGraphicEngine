#include "QuadScreenCamera.h"

namespace ege
{
    QuadScreenCamera::QuadScreenCamera()
        : OrthographicCamera(CameraType::QuadScreenCamera)
    {
    }

    QuadScreenCamera::~QuadScreenCamera()
    {
    }

    void QuadScreenCamera::Update()
    {
        Camera::Update();
    }

    void QuadScreenCamera::ComputeProjectionMatrix()
    {
        UINT windowWidth = gWindow().GetWindowWidth();
        UINT windowHeight = gWindow().GetWindowHeight();

        XMMATRIX Projection = XMMatrixOrthographicOffCenterLH(
            (((-(INT)windowWidth) / 2.0f) + _position.x - 1.0f) * _zoom,
            ((windowWidth / 2.0f) + _position.x - 1.0f) * _zoom,
            (((-(INT)windowHeight) / 2.0f) + _position.y) * _zoom,
            ((windowHeight / 2.0f) + _position.y) * _zoom,
            -512.0f + _position.y,
            512.0f + _position.y);

        XMVECTOR Right = XMVectorSet(_position.x, _position.y, 0.0f, 0.0f);
        XMVECTOR Up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
        XMVECTOR Look = XMVectorSet(_position.x, _position.y, 1.0f, 0.0f);

        XMMATRIX View = XMMatrixLookAtLH(Right, Look, Up);

        XMStoreFloat4x4(&_projection, Projection);
        XMStoreFloat4x4(&_view, View);
    }
}