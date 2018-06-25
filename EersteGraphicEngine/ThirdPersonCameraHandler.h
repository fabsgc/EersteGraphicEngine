#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    struct ThirdPersonCameraHandlerConfig
    {
        XMFLOAT3 StartPosition;
        float    StartAlpha;
        float    StartBeta;
        float    ZoomSpeed;
        float    Radius;
    };

    class ThirdPersonCameraHandler: public ICameraHandler<ThirdPersonCamera>
    {
    public:
        ThirdPersonCameraHandler(
            XMFLOAT3 position = MathUtility::Zero,
            float zoomSpeed = DefaultZoomSpeed, 
            float radius = DefaultRadius, 
            float alpha = DefaultStartAlpha, 
            float beta = DefaultStartBeta
        );

        virtual void InitialiseCameraHandler() override;
        void         UpdateCamera(XMFLOAT3 position, XMFLOAT2 rotation);

    protected:
        const static float DefaultZoomSpeed;
        const static float DefaultRadius;
        const static float DefaultStartAlpha;
        const static float DefaultStartBeta;

    protected:
        ThirdPersonCameraHandlerConfig _cameraConfig;
    };
}