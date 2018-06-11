#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"
#include "Frustum.h"

namespace ege
{
    class PerspectiveCamera : public Camera
    {
    public:
        PerspectiveCamera(CameraType type);
        virtual ~PerspectiveCamera();

        void              Update();
        virtual void      ComputeProjectionMatrix() override {};

        const float&      GetRotationSpeed() const;
        virtual void      Pitch(float angle);
        virtual void      Roll(float angle);
        virtual void      Yaw(float angle);
        const XMFLOAT3&   GetRight() const;
        const XMFLOAT3&   GetLook() const;
        const XMFLOAT3&   GetUp() const;
        const float&      GetFov() const;

    public:
        static const float DefaultFov;
        static const float DefaultRotationSpeed;

    protected:
        float              _fov;
        float              _rotationSpeed;

        Frustum            _frustum;
    };
}