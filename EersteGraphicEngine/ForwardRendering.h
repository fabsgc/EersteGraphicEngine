#pragma once

#include "PrerequisitesCore.h"
#include "RenderPipeline.h"

namespace ege
{
    class ForwardRendering : public RenderPipeline
    {
    public:
        ForwardRendering() {};
        ~ForwardRendering() {};
        virtual void Draw() override {};
    };
}