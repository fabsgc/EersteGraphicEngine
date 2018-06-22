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
        Model::Update();
    }
}