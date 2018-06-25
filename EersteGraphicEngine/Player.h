#pragma once

#include "PrerequisitesCore.h"
#include "ThirdPersonCameraHandler.h"
#include "OrthographicCameraHandler.h"
#include "InputHandler.h"
#include "Joypad.h"
#include "Mouse.h"
#include "Time.h"
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

    protected:
        InputHandler& _inputHandler;
        Keyboard&     _keyboard;
        Joypad&       _joypad;
        Mouse&        _mouse;
        Time&         _time;
    };
}