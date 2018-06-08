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
    };
}