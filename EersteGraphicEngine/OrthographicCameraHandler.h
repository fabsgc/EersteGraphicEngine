#pragma once

#include "PrerequisitesCore.h"
#include "OrthographicCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    class OrthographicCameraHandler : public ICameraHandler<OrthographicCamera>
    {
    public:
        void UpdateCamera();
    };
}