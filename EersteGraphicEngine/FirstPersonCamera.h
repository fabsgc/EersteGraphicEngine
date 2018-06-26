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

        void Update() override;
        void Walk(float distance) override;
        void Strafe(float x, float y, float z) override;
        void Strafe(XMFLOAT3 distance) override;
    };
}