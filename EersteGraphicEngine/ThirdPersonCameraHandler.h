#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCamera.h"
#include "ICameraHandler.h"

namespace ege
{
    class ThirdPersonCameraHandler: public ICameraHandler<ThirdPersonCamera>
    {
    public:
        ThirdPersonCameraHandler(float zoomSpeed = DefaultZoomSpeed);
        void UpdateCamera(XMFLOAT3 position, float pitch, float yaw);

    protected:
        const static float DefaultZoomSpeed;

    protected:
        Keyboard & _keyboard;
        Joypad&    _joypad;
        Mouse&     _mouse;
        Time&      _time;

        float      _translationSpeed;
        float      _rotationSpeed;
        float      _zoomSpeed;
    };
}