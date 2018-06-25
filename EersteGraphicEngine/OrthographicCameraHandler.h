#pragma once

#include "PrerequisitesCore.h"
#include "OrthographicCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    struct OrthographicCameraHandlerConfig
    {
        XMFLOAT3 StartPosition;
        float    StartZoom;
        float    ZoomSpeed;
    };

    class OrthographicCameraHandler : public ICameraHandler<OrthographicCamera>
    {
    public:
        OrthographicCameraHandler(XMFLOAT3 position = MathUtility::Zero, float zoom = DefaultZoom, float zoomSpeed = DefaultZoomSpeed);
        ~OrthographicCameraHandler() {};

        virtual void InitialiseCameraHandler() override;
        void         UpdateCamera(XMFLOAT3 movement);

    protected:
        const static float DefaultZoomSpeed;
        const static float DefaultZoom;

    protected:
        OrthographicCameraHandlerConfig _cameraConfig;
    };
}