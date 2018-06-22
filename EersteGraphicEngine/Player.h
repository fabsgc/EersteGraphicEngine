#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCameraHandler.h"
#include "Cube.h"

namespace ege
{
    class Player : public Cube, public ThirdPersonCameraHandler
    {
    public:
        Player();
        ~Player();
        void Update();
    };
}