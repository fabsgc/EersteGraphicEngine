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
        virtual void Strafe(float x, float y, float z);
        virtual void Strafe(XMFLOAT3 distance);
        void         Pitch(float angle) override;
        void         Roll(float angle) override;
        void         Yaw(float angle) override;

        virtual void Move(XMVECTOR movement) override;
        virtual void Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override;
        virtual void Rotate(XMVECTOR eulerAngles) override;
    };
}