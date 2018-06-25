#include "OrthographicCameraHandler.h"

namespace ege
{
    const float OrthographicCameraHandler::DefaultZoomSpeed = 0.75f;
    const float OrthographicCameraHandler::DefaultZoom      = 0.4f;

    OrthographicCameraHandler::OrthographicCameraHandler(XMFLOAT3 position, float zoom, float zoomSpeed)
        : ICameraHandler()
    {
        _cameraConfig.StartPosition = position;
        _cameraConfig.StartZoom     = zoom;
        _cameraConfig.ZoomSpeed     = zoomSpeed;
    }

    void OrthographicCameraHandler::InitialiseCameraHandler()
    {
        XMFLOAT3 position = XMFLOAT3(
            _cameraConfig.StartPosition.x,
            _cameraConfig.StartPosition.z,
            _cameraConfig.StartPosition.y
        );

        _camera->SetPosition(position);
        _camera->SetZoom(_cameraConfig.StartZoom);
        ICameraHandler::InitialiseCameraHandler();
    }

    void OrthographicCameraHandler::UpdateCamera(XMFLOAT3 movement)
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

        if (_inputHandler.GetState("ZOOM_UP").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(deltaTime * _cameraConfig.ZoomSpeed);
        else if (_inputHandler.GetState("ZOOM_DOWN").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(-deltaTime * _cameraConfig.ZoomSpeed);

        _camera->Strafe(movement);

        _camera->ComputeProjectionMatrix();
    }
}