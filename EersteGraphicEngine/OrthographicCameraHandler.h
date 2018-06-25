#pragma once

#include "PrerequisitesCore.h"
#include "OrthographicCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    struct OrthographicCameraHandlerConfig
    {
        XMFLOAT3 StartPosition;
    };

    class OrthographicCameraHandler : public ICameraHandler<OrthographicCamera>
    {
    public:
        OrthographicCameraHandler(XMFLOAT3 position);
        ~OrthographicCameraHandler() {};

        virtual void InitialiseCameraHandler() override;
        void         UpdateCamera();

    protected:
        OrthographicCameraHandlerConfig _cameraConfig;
    };
}