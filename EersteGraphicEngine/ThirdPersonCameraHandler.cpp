#include "ThirdPersonCameraHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    const float ThirdPersonCameraHandler::DefaultZoomSpeed        = 64.0f;

    ThirdPersonCameraHandler::ThirdPersonCameraHandler(float zoomSpeed)
        : _zoomSpeed(zoomSpeed)
        , _keyboard(gKeyboard())
        , _joypad(gJoypad())
        , _mouse(gMouse())
        , _time(gTime())
    {
    }

    void ThirdPersonCameraHandler::UpdateCamera(XMFLOAT3 position, float pitch, float yaw)
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

        _camera->SetTarget(position);
        _camera->Yaw(yaw);
        _camera->Pitch(-pitch);

        _camera->ComputeProjectionMatrix();
    }
}