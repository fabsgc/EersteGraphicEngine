#include "Player.h"

#include "Time.h"
#include "Mouse.h"
#include "Joypad.h"

namespace ege
{
    const float Player::DefaultTranslationSpeed = 30.0f;
    const float Player::DefaultRotationSpeed    = 5.0f;

    Player::Player(float translationSpeed, float rotationSpeed)
        : Cube()
        , ThirdPersonCameraHandler(_position)
        , _inputHandler(gInputHandler())
        , _keyboard(gKeyboard())
        , _joypad(gJoypad())
        , _mouse(gMouse())
        , _time(gTime())
    {
    }

    Player::~Player()
    {
    }

    void Player::Update()
    {
        /*float deltaTime   = _time.GetFrameDelta();
        float translation = MathUtility::FloatPrecision(DefaultTranslationSpeed * deltaTime, 2.0f);
        float rotation    = MathUtility::FloatPrecision(DefaultRotationSpeed * deltaTime, 2.0f);
        XMFLOAT2 angles   = XMFLOAT2(0.0f, 0.0f);
        XMFLOAT3 movement = XMFLOAT3(0.0f, 0.0f, 0.0f);
        bool hasMoved     = false;

        if (_inputHandler.GetState("GO_FORWARD").State == InputHandlerState::TRIGGERED)
        {
            MoveStrafeZ(translation);
            movement.y = translation;
            hasMoved = true;
        } 
        else if (_inputHandler.GetState("GO_BACKWARD").State == InputHandlerState::TRIGGERED)
        {
            MoveStrafeZ(-translation);
            movement.y = -translation;
            hasMoved = true;
        }
        if (_inputHandler.GetState("GO_LEFT").State == InputHandlerState::TRIGGERED)
        {
            MoveStrafeX(-translation);
            movement.x = -translation;
            hasMoved = true;
        }
        else if (_inputHandler.GetState("GO_RIGHT").State == InputHandlerState::TRIGGERED)
        {
            MoveStrafeX(translation);
            movement.x = translation;
            hasMoved = true;
        }
        
        XMFLOAT2 relativeMovement = gMouse().GetRelativeMovement();
        angles.x = MathUtility::FloatPrecision(relativeMovement.x * deltaTime, 2.0f);
        angles.y = MathUtility::FloatPrecision(relativeMovement.y * deltaTime, 2.0f);

        if (abs(angles.x) < 0.01f)
            angles.x = 0.0f;
        if (abs(angles.y) < 0.01f)
            angles.y = 0.0f;

        if (_joypad.IsConnected())
        {
            float joypadLX = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisX;
            float joypadLY = (float)_joypad.GetJoyStick(JoypadStickName::LEFT).AxisY;

            if (angles.x == 0.0f && angles.y == 0.0f)
            {
                float joypadRX = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisX;
                float joypadRY = (float)_joypad.GetJoyStick(JoypadStickName::RIGHT).AxisY;

                if (angles.x == 0.0f)
                    angles.x = MathUtility::FloatPrecision(joypadRX * rotation, 2.0f);
                if (angles.y == 0.0f)
                    angles.y = MathUtility::FloatPrecision(-joypadRY * rotation, 2.0f);
            }

            if (abs(joypadLY) > 0.0f)
            {
                MoveStrafeZ(joypadLY * translation);
                movement.y = joypadLY * translation;
                hasMoved = true;
            }
            if (abs(joypadLX) > 0.0f)
            {
                MoveStrafeX(joypadLX * translation);
                movement.x = joypadLX * translation;
                hasMoved = true;
            }
        }

        if (abs(angles.x) < 0.01f)
            angles.x = 0;
        if (abs(angles.y) < 0.01f)
            angles.y = 0;

        if (angles.x != 0.0f || angles.y != 0.0f)
        {
            RotatePitch(angles.x);
            hasMoved = true;
        }

        if (HasCamera())
        {
            UpdateCamera(_position, angles);
        }*/

        Model::Update();
    }
}