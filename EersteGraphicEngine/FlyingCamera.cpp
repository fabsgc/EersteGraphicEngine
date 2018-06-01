#include "FlyingCamera.h"
#include "Keyboard.h"
#include "Mouse.h"

namespace ege
{
    FlyingCamera::FlyingCamera()
        : Camera()
    {
    }

    FlyingCamera::~FlyingCamera()
    {
    }

    void FlyingCamera::Update()
    {
        Keyboard& keyboard = gKeyboard();
        Mouse& mouse       = gMouse();

        Camera::Update();
    }
}