#pragma once

#include "PrerequisitesCore.h"
#include "PerspectiveCamera.h"

namespace ege
{
    class FlyingCamera : public PerspectiveCamera
    {
    public:
        FlyingCamera();
        FlyingCamera(CameraType type);
        ~FlyingCamera();

        void         Update();
        void         ComputeProjectionMatrix() override;

        virtual void Walk(float distance);
        virtual void Move(XMFLOAT3 distance) override;
        void         Pitch(float angle) override;
        void         Roll(float angle) override;
        void         Yaw(float angle) override;
    };
}