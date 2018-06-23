#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCameraHandler.h"
#include "Cube.h"

namespace ege
{
    class Player : public Cube, public ThirdPersonCameraHandler
    {
    public:
        Player(float translationSpeed = DefaultTranslationSpeed, float rotationSpeed = DefaultRotationSpeed);
        ~Player();
        void Update();

    protected:
        const static float DefaultTranslationSpeed;
        const static float DefaultRotationSpeed;
    };
}