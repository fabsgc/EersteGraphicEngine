#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class FlyingCamera : public Camera
    {
    public:
        FlyingCamera();
        FlyingCamera(CameraType type);
        ~FlyingCamera();

        void         Update();
        void         ComputeProjectionMatrix() override;

        virtual void Walk(float distance);
        virtual void Move(XMFLOAT3 distance);
        void         Move(float x, float y, float z);
        void         MoveX(float x);
        void         MoveY(float y);
        void         MoveZ(float z);
        void         Pitch(float angle) override;
        void         Roll(float angle) override;
        void         Yaw(float angle) override;
    };
}