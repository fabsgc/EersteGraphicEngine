#pragma once

#include "PrerequisitesCore.h"
#include "Cube.h"

namespace ege
{
    class Player : public Cube
    {
    public:
        Player(SPtr<Camera> camera);
        ~Player();
        void Update();

    protected:
        SPtr<Camera> _camera;
    };
}