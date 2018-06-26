#pragma once

#include "PrerequisitesCore.h"
#include "PerspectiveCamera.h"

namespace ege
{
    class ThirdPersonCamera : public PerspectiveCamera
    {
    public:
        ThirdPersonCamera();
        ~ThirdPersonCamera();

        void     Initialise() override;
        void     Update();
        void     ComputeProjectionMatrix() override;

        void     LookAt(XMFLOAT3 position, XMFLOAT3 target, XMFLOAT3 up);
        void     Pitch(float angle) override;
        void     Yaw(float angle) override;
        void     Strafe(float distance);
        void     Walk(float distance);
        void     Up(float distance);
        void     Zoom(float zoom);

        void     SetTarget(XMFLOAT3 target);
        void     SetRadius(float radius);

        void     SetAlpha(float alpha);
        void     SetBeta(float beta);

        void     SetZoomSpeed(float zoomSpeed);

        XMFLOAT3 GetTarget();

    protected:
        static const float    DefaultZoomSpeed;
        const static float    DefaultRadius;
        const static float    DefaultStartAlpha;
        const static float    DefaultStartBeta;
        static const float    DefaultMinZoom;
        static const float    DefaultMaxZoom;
        static const XMFLOAT3 DefaultTarget;

    protected:
        XMFLOAT3 _target;
        float    _radius;
        float    _alpha;
        float    _beta;
        float    _zoomSpeed;
        float    _minZoom;
        float    _maxZoom;

        XMFLOAT2 _lastMousePosition;
    };
}