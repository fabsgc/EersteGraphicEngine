#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class ThirdPersonCamera : public Camera
    {
    public:
        ThirdPersonCamera();
        ~ThirdPersonCamera();

        void Update();
    };
}