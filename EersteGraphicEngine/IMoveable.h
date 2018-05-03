#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class IMoveable
    {
    public:
        IMoveable() {}
        virtual ~IMoveable() = 0 {}

    protected:
        XMFLOAT4X4 _world;
        XMFLOAT3   _position;
    };
}