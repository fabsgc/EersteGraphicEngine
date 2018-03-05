#pragma once

#include "PrerequisitesCore.h"

namespace ege
{
    class IDrawable
    {
    public:
        IDrawable() {}
        virtual ~IDrawable() = 0 {}
        virtual void Draw();
    };
}