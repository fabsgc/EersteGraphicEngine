#include "Player.h"

#include "Time.h"
#include "Mouse.h"
#include "Joypad.h"
#include "Keyboard.h"

namespace ege
{
    Player::Player()
        : Cube()
    {
    }

    Player::~Player()
    {
    }

    void Player::Update()
    {
        float deltaTime = gTime().GetFrameDelta();
        float angleX = 0.0f;
        float angleY = 0.0f;

        if (gKeyboard().GetState(KeyName::ARROW_UP) == KeyState::TRIGGERED)
        {
            MoveStrafeZ(10.0f * deltaTime);
        }
        if (gKeyboard().GetState(KeyName::ARROW_DOWN) == KeyState::TRIGGERED)
        {
            MoveStrafeZ(-10.0f * deltaTime);
        }
        if (gKeyboard().GetState(KeyName::ARROW_LEFT) == KeyState::TRIGGERED)
        {
            MoveStrafeX(-10.0f * deltaTime);
        }
        if (gKeyboard().GetState(KeyName::ARROW_RIGHT) == KeyState::TRIGGERED)
        {
            MoveStrafeX(10.0f * deltaTime);
        }

        XMFLOAT2 relativeMovement = gMouse().GetRelativeMovement();
        angleX = relativeMovement.x * deltaTime;
        angleY = relativeMovement.y * deltaTime;

        if (abs(angleX) < 0.01f)
            angleX = 0.0f;

        if (abs(angleY) < 0.01f)
            angleY = 0.0f;

        if (gJoypad().IsConnected())
        {
            float joypadRX = (float)gJoypad().GetJoyStick(JoypadStickName::RIGHT).AxisX * 300.0f;
            float joypadRY = (float)gJoypad().GetJoyStick(JoypadStickName::RIGHT).AxisY * 300.0f;

            float joypadLX = (float)gJoypad().GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)gJoypad().GetJoyStick(JoypadStickName::LEFT).AxisY;

            if(angleX == 0.0f)
                angleX = joypadRX * deltaTime * MathUtility::G_PI / 180.0f * 2.0f;
            if(angleY == 0.0f)
            angleY = -joypadRY * deltaTime * MathUtility::G_PI / 180.0f * 2.0f;

            if (abs(joypadLY) > 0.0f)
                MoveStrafeZ(joypadLY * deltaTime *  10.0f);
            if (abs(joypadLX) > 0.0f)
                MoveStrafeX(joypadLX * deltaTime *  10.0f);
        }

        if (abs(angleX) < 0.01f)
            angleX = 0;

        if (abs(angleY) < 0.01f)
            angleY = 0;

        RotatePitch(angleX);
        UpdateLocalPosition();

        if (HasCamera())
        {
            UpdateCamera(_position, angleX, angleY);
        }

        Model::Update();
    }
}