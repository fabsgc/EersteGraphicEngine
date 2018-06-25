#pragma once

#include "PrerequisitesCore.h"
#include "FirstPersonCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    struct FirstPersonCameraHandlerConfig
    {
        XMFLOAT3 StartPosition;
    };

    class FirstPersonCameraHandler : public ICameraHandler<FirstPersonCamera>
    {
    public:
        FirstPersonCameraHandler(XMFLOAT3 position);
        ~FirstPersonCameraHandler() {};

        virtual void InitialiseCameraHandler() override;
        void         UpdateCamera(XMFLOAT3 translation, XMFLOAT2 rotation);

    protected:
        FirstPersonCameraHandlerConfig _cameraConfig;
    };
}