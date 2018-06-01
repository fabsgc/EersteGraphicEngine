#include "FlyingCamera.h"

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
        Camera::Update();
    }
}