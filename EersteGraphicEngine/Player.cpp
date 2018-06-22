#include "Player.h"

#include "Time.h"
#include "Keyboard.h"

namespace ege
{
    Player::Player(SPtr<Camera> camera)
        : Cube()
        , _camera(camera)
    {
    }

    Player::~Player()
    {
    }

    void Player::Update()
    {
        float deltaTime = gTime().GetFrameDelta();

        if (gKeyboard().GetState(KeyName::ARROW_UP) == KeyState::TRIGGERED)
        {
            MoveZ(5.0f * deltaTime);
        }

        if (gKeyboard().GetState(KeyName::ARROW_DOWN) == KeyState::TRIGGERED)
        {
            MoveZ(-5.0f * deltaTime);
        }

        if (gKeyboard().GetState(KeyName::ARROW_LEFT) == KeyState::TRIGGERED)
        {
            MoveX(-5.0f * deltaTime);
        }

        if (gKeyboard().GetState(KeyName::ARROW_RIGHT) == KeyState::TRIGGERED)
        {
            MoveX(5.0f * deltaTime);
        }

        Model::Update();
    }
}