#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class IUpdatable
    {
    public:
        IUpdatable() {}
        virtual ~IUpdatable() = 0 {}
        virtual void Update();
    };
}