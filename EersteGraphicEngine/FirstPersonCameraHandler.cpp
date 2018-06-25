#include "FirstPersonCameraHandler.h"

namespace ege
{
    FirstPersonCameraHandler::FirstPersonCameraHandler(XMFLOAT3 position)
        : ICameraHandler()
    {
        _cameraConfig.StartPosition = position;
    }

    void FirstPersonCameraHandler::InitialiseCameraHandler()
    {
        _camera->SetPosition(_cameraConfig.StartPosition);
        ICameraHandler::InitialiseCameraHandler();
    }

    void FirstPersonCameraHandler::UpdateCamera(XMFLOAT3 translation, XMFLOAT2 rotation)
    {
        _camera->Yaw(rotation.y);
        _camera->Pitch(-rotation.x);

        _camera->Walk(translation.z);
        _camera->MoveX(translation.x);

        _camera->ComputeProjectionMatrix();
    }
}