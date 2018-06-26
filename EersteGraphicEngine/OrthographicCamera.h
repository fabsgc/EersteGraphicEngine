#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class OrthographicCamera : public Camera
    {
    public:
        OrthographicCamera();
        ~OrthographicCamera();

        void         Update();
        virtual void ComputeProjectionMatrix() override;
        virtual void Strafe(float x, float y, float z);
        virtual void Strafe(XMFLOAT3 distance);
        void         Zoom(float zoom);

        using        Camera::Move;
        using        Camera::MoveStrafe;
        using        Camera::Rotate;
        virtual void Move(XMVECTOR movement) override {};
        virtual void MoveStrafe(XMVECTOR movement) override {};
        virtual void Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void Rotate(XMVECTOR eulerAngles) override {};

        void         SetPosition(XMFLOAT3 position);
        void         SetZoom(float zoom);

    public:
        static const float DefaultZoomSpeed;
        static const float DefaultMinZoom;
        static const float DefaultMaxZoom;

    protected:
        float    _zoom;
        float    _zoomSpeed;
        XMFLOAT2 _lastMousePosition;
    };
}