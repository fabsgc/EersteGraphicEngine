#include "OrthographicCameraHandler.h"

namespace ege
{
    OrthographicCameraHandler::OrthographicCameraHandler(XMFLOAT3 position)
        : ICameraHandler()
    {
        _cameraConfig.StartPosition = position;
    }

    void OrthographicCameraHandler::InitialiseCameraHandler()
    {
        _camera->SetPosition(_cameraConfig.StartPosition);
        _camera->ComputeProjectionMatrix();
    }

    void OrthographicCameraHandler::UpdateCamera()
    {
    }
}