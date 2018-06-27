#pragma once

#include "PrerequisitesCore.h"
#include "RenderAPI.h"

namespace ege
{
    class Effect
    {
    public:
        Effect();
        virtual ~Effect() = 0;

    protected:
        RenderAPI & _renderAPI;
    };
}