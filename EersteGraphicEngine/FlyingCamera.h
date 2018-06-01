#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class FlyingCamera : public Camera
    {
    public:
        FlyingCamera();
        ~FlyingCamera();

        void Update();
    };
}