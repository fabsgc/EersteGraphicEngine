#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    class ThirdPersonCameraHandler: public ICameraHandler<ThirdPersonCamera>
    {
    public:
        void UpdateCamera(XMFLOAT3 position, float pitch, float yaw);
    };
}