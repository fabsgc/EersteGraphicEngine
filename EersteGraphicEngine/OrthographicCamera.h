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
        virtual void Move(XMFLOAT3 distance) override;
        void         Zoom(float zoom);

    public:
        static const float DefaultMinZoom;
        static const float DefaultMaxZoom;

    protected:
        float    _zoom;
        XMFLOAT2 _lastMousePosition;
    };
}