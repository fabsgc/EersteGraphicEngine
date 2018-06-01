#pragma once

#include "PrerequisitesCore.h"
#include "Camera.h"

namespace ege
{
    class FirstPersonCamera : public Camera
    {
    public:
        FirstPersonCamera();
        ~FirstPersonCamera();

        void Update();
    };
}