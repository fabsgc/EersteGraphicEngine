#include "PerspectiveCamera.h"

namespace ege
{
    const float PerspectiveCamera::DefaultFov   = XM_PIDIV4;
    const float PerspectiveCamera::DefaultRotationSpeed = 0.25f;

    PerspectiveCamera::PerspectiveCamera(CameraType type)
        : Camera(type)
        , _fov(DefaultFov)
        , _rotationSpeed(DefaultRotationSpeed)
    {
    }

    PerspectiveCamera::~PerspectiveCamera()
    {
    }

    void PerspectiveCamera::Update()
    {
        _frustum.Build(this);
        Camera::Update();
    }

    void PerspectiveCamera::Pitch(float angle)
    {}

    void PerspectiveCamera::Roll(float angle)
    {}

    void PerspectiveCamera::Yaw(float angle)
    {}

    const float& PerspectiveCamera::GetRotationSpeed() const
    {
        return _rotationSpeed;
    }

    const XMFLOAT3& PerspectiveCamera::GetRight() const
    {
        return _right;
    }

    const XMFLOAT3& PerspectiveCamera::GetLook() const
    {
        return _look;
    }

    const XMFLOAT3& PerspectiveCamera::GetUp() const
    {
        return _up;
    }

    const float& PerspectiveCamera::GetFov() const
    {
        return _fov;
    }

    const Frustum& PerspectiveCamera::GetFrustum() const
    {
        return _frustum;
    }

    const Frustum* PerspectiveCamera::GetFrustumPtr() const
    {
        return &_frustum;
    }
}