#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class ThirdPersonCamera : public Camera
    {
    public:
        ThirdPersonCamera();
        ~ThirdPersonCamera();

        void Initialise() override;
        void Update();
        void ComputeProjectionMatrix() override;

        void LookAt(XMFLOAT3 position, XMFLOAT3 target, XMFLOAT3 up);
        void Pitch(float angle) override;
        void Yaw(float angle) override;
        void Strafe(float distance);
        void Walk(float distance);
        void Up(float distance);
        void Zoom(float zoom);

    protected:
        static const float DefaultMinZoom;
        static const float DefaultMaxZoom;

    protected:
        XMFLOAT3 _target;
        float    _radius;
        float    _alpha;
        float    _beta;
        float    _minZoom;
        float    _maxZoom;

        XMFLOAT2 _lastMousePosition;
    };
}