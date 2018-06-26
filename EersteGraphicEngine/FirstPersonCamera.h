#pragma once

#include "PrerequisitesCore.h"
#include "FlyingCamera.h"

namespace ege
{
    class FirstPersonCamera : public FlyingCamera
    {
    public:
        FirstPersonCamera();
        ~FirstPersonCamera();

        void         Update() override;
        void         Walk(float distance) override;
        void         Strafe(float x, float y, float z) override;
        void         Strafe(XMFLOAT3 distance) override;

        using        FlyingCamera::Move;
        using        FlyingCamera::MoveStrafe;
        using        FlyingCamera::Rotate;
        virtual void Move(XMVECTOR movement) override {};
        virtual void MoveStrafe(XMVECTOR movement) override {};
        virtual void Rotate(XMVECTOR origin, XMVECTOR eulerAngles) override {};
        virtual void Rotate(XMVECTOR eulerAngles) override {};
    };
}