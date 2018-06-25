#include "ThirdPersonCameraHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    const float ThirdPersonCameraHandler::DefaultZoomSpeed  = 64.0f;
    const float ThirdPersonCameraHandler::DefaultRadius     = 32.0f;
    const float ThirdPersonCameraHandler::DefaultStartAlpha = -XM_PIDIV2;
    const float ThirdPersonCameraHandler::DefaultStartBeta  = 0.0f;

    ThirdPersonCameraHandler::ThirdPersonCameraHandler(XMFLOAT3 position, float zoomSpeed, float radius, float alpha, float beta)
    {
        _cameraConfig.StartPosition = position;
        _cameraConfig.ZoomSpeed     = zoomSpeed;
        _cameraConfig.Radius        = radius;
        _cameraConfig.StartAlpha    = alpha;
        _cameraConfig.StartBeta     = beta;
    }

    void ThirdPersonCameraHandler::InitialiseCameraHandler()
    {
        _camera->SetTarget(_cameraConfig.StartPosition);
        _camera->SetAlpha(_cameraConfig.StartAlpha);
        _camera->SetBeta(_cameraConfig.StartBeta);
        _camera->SetRadius(_cameraConfig.Radius);

        _camera->ComputeProjectionMatrix();
    }

    void ThirdPersonCameraHandler::UpdateCamera(XMFLOAT3 position, XMFLOAT2 rotation)
    {
        float deltaTime = _time.GetFrameDelta();

        MouseWheelState mouseWheelState = _mouse.GetWheelState();
        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            _camera->Zoom(deltaTime * DefaultZoomSpeed);
            break;

        case MouseWheelState::ROLL_DOWN:
            _camera->Zoom(-deltaTime * DefaultZoomSpeed);
            break;
        }

        if (gInputHandler().GetState("ZOOM_UP").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(deltaTime * DefaultZoomSpeed);
        else if (gInputHandler().GetState("ZOOM_DOWN").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(-deltaTime * DefaultZoomSpeed);

        _camera->Yaw(rotation.y);
        _camera->Pitch(-rotation.x);
        _camera->SetTarget(position);

        _camera->ComputeProjectionMatrix();
    }
}