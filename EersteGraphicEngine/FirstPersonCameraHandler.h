#pragma once

#include "PrerequisitesCore.h"
#include "FirstPersonCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    class FirstPersonCameraHandler : public ICameraHandler<FirstPersonCamera>
    {
    public:
        void UpdateCamera();
    };
}