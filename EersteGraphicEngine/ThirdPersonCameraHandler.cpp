#include "ThirdPersonCameraHandler.h"
#include "Window.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"

namespace ege
{
    void ThirdPersonCameraHandler::UpdateCamera(XMFLOAT3 position, float pitch, float yaw)
    {
        Keyboard& keyboard = gKeyboard();
        Joypad& joypad = gJoypad();
        Mouse& mouse = gMouse();
        Time& time = gTime();
        float deltaTime = time.GetFrameDelta();

        MouseWheelState mouseWheelState = mouse.GetWheelState();
        switch (mouseWheelState)
        {
        case MouseWheelState::ROLL_UP:
            _camera->Zoom(deltaTime * 64.0f);
            break;

        case MouseWheelState::ROLL_DOWN:
            _camera->Zoom(-deltaTime * 64.0f);
            break;
        }

        if (gInputHandler().GetState("ZOOM_UP").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(deltaTime * 64.0f);
        else if (gInputHandler().GetState("ZOOM_DOWN").State == InputHandlerState::TRIGGERED)
            _camera->Zoom(-deltaTime * 64.0f);

        _camera->SetTarget(position);
        _camera->Yaw(yaw);
        _camera->Pitch(-pitch);

        _camera->ComputeProjectionMatrix();
    }
}